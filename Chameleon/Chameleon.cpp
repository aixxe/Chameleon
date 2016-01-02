/*

	Chameleon - basic skin & knife changer for Counter-Strike: Global Offensive.
	Copyright (C) 2014 - 2015, Team SkyeNet. (www.skyenet.org)
	
	Contributors:
		* aixxe <aixxe@skyenet.org>

*/

// Include the game classes.
#include "SDK.h"

// Include the user defined skins.
#include "Skins.h"

// Include the NetVar proxy functions.
#include "Proxies.h"

// Define the calling convention for the FrameStageNotify function.
typedef void(__thiscall *FrameStageNotify)(void*, ClientFrameStage_t);
FrameStageNotify fnOriginalFunction = NULL;

// Function to apply skin data to weapons.
inline bool ApplyCustomSkin(CBaseAttributableItem* pWeapon, int nWeaponIndex) {
	// Check if this weapon has a valid override defined.
	if (g_SkinChangerCfg.find(nWeaponIndex) == g_SkinChangerCfg.end())
		return false;

	// Apply our changes to the fallback variables.
	*pWeapon->GetFallbackPaintKit() = g_SkinChangerCfg[nWeaponIndex].nFallbackPaintKit;
	*pWeapon->GetEntityQuality() = g_SkinChangerCfg[nWeaponIndex].iEntityQuality;
	*pWeapon->GetFallbackSeed() = g_SkinChangerCfg[nWeaponIndex].nFallbackSeed;
	*pWeapon->GetFallbackStatTrak() = g_SkinChangerCfg[nWeaponIndex].nFallbackStatTrak;
	*pWeapon->GetFallbackWear() = g_SkinChangerCfg[nWeaponIndex].flFallbackWear;

	if (g_SkinChangerCfg[nWeaponIndex].iItemDefinitionIndex)
		*pWeapon->GetItemDefinitionIndex() = g_SkinChangerCfg[nWeaponIndex].iItemDefinitionIndex;

	// If a name is defined, write it now.
	if (g_SkinChangerCfg[nWeaponIndex].szCustomName) {
		sprintf_s(pWeapon->GetCustomName(), 32, "%s", g_SkinChangerCfg[nWeaponIndex].szCustomName);
	}

	// Edit "m_iItemIDHigh" so fallback values will be used.
	*pWeapon->GetItemIDHigh() = -1;

	return true;
}

// Function to apply custom view models to weapons.
inline bool ApplyCustomModel(CBasePlayer* pLocal, CBaseAttributableItem* pWeapon, int nWeaponIndex) {
	// Get the view model of this weapon.
	CBaseViewModel* pViewModel = pLocal->GetViewModel();
	
	if (!pViewModel)
		return false;

	// Get the weapon belonging to this view model.
	DWORD hViewModelWeapon = pViewModel->GetWeapon();
	CBaseAttributableItem* pViewModelWeapon = (CBaseAttributableItem*)g_EntityList->GetClientEntityFromHandle(hViewModelWeapon);

	if (pViewModelWeapon != pWeapon)
		return false;

	// Check if an override exists for this view model.
	int nViewModelIndex = pViewModel->GetModelIndex();

	if (g_ViewModelCfg.find(nViewModelIndex) == g_ViewModelCfg.end())
		return false;
	
	// Set the replacement model.
	pViewModel->SetWeaponModel(g_ViewModelCfg[nViewModelIndex], pWeapon);
	
	return true;
}

void __fastcall FrameStageNotifyThink(void* ecx, void* edx, ClientFrameStage_t Stage) {
	while (Stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
		// Populate g_ViewModelCfg while in-game so IVModelInfoClient::GetModelIndex returns correctly.
		if (g_ViewModelCfg.size() == 0)
			SetModelConfig();

		// Get our player entity.
		int nLocalPlayerID = g_EngineClient->GetLocalPlayer();
		CBasePlayer* pLocal = (CBasePlayer*)g_EntityList->GetClientEntity(nLocalPlayerID);

		// Don't change anything if we're not alive.
		if (!pLocal || pLocal->GetLifeState() != LIFE_ALIVE)
			break;

		// Get handles to weapons we're carrying.
		UINT* hWeapons = pLocal->GetWeapons();

		if (!hWeapons)
			break;

		// Retrieve our player information which will be used for ownership checking.
		player_info_t LocalPlayerInfo;
		g_EngineClient->GetPlayerInfo(nLocalPlayerID, &LocalPlayerInfo);

		// Loop through weapons and run our skin function on them.
		for (int nIndex = 0; hWeapons[nIndex]; nIndex++) {
			// Get the weapon entity from the provided handle.
			CBaseAttributableItem* pWeapon = (CBaseAttributableItem*)g_EntityList->GetClientEntityFromHandle(hWeapons[nIndex]);

			if (!pWeapon)
				continue;

			// Get the weapons item definition index.
			int nWeaponIndex = *pWeapon->GetItemDefinitionIndex();

			ApplyCustomModel(pLocal, pWeapon, nWeaponIndex);

			// Compare original owner XUIDs.
			if (LocalPlayerInfo.m_nXuidLow != *pWeapon->GetOriginalOwnerXuidLow())
				continue;

			if (LocalPlayerInfo.m_nXuidHigh != *pWeapon->GetOriginalOwnerXuidHigh())
				continue;

			ApplyCustomSkin(pWeapon, nWeaponIndex);

			// Fix up the account ID so StatTrak will display correctly.
			*pWeapon->GetAccountID() = LocalPlayerInfo.m_nXuidLow;
		}

		break;
	}

	// Run the original FrameStageNotify function.
	fnOriginalFunction(ecx, Stage);
}

void Initialise() {
	// Get the "CreateInterface" function from "client.dll" and "engine.dll".
	CreateInterfaceFn fnClientFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("client.dll"), "CreateInterface");
	CreateInterfaceFn fnEngineFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface");
	
	// Call "CreateInterface" to get the required class pointers.
	g_BaseClient = (IBaseClientDLL*)fnClientFactory("VClient017", NULL); 
	g_EntityList = (IClientEntityList*)fnClientFactory("VClientEntityList003", NULL);
	g_EngineClient = (IVEngineClient*)fnEngineFactory("VEngineClient013", NULL);
	g_ModelInfo = (IVModelInfoClient*)fnEngineFactory("VModelInfoClient004", NULL);
	
	// Get the virtual method table for IBaseClientDLL.
	PDWORD* pClientDLLVMT = (PDWORD*)g_BaseClient;

	// Save the untouched table so we know where the original functions are.
	PDWORD pOriginalClientDLLVMT = *pClientDLLVMT;

	// Calculate the size of the table.
	size_t dwVMTSize = 0;

	while ((PDWORD)(*pClientDLLVMT)[dwVMTSize])
		dwVMTSize++;

	// Create the replacement table.
	PDWORD pNewClientDLLVMT = new DWORD[dwVMTSize];

	// Copy the original table into the replacement table.
	CopyMemory(pNewClientDLLVMT, pOriginalClientDLLVMT, (sizeof(DWORD) * dwVMTSize));

	// Change the FrameStageNotify function in the new table to point to our function.
	pNewClientDLLVMT[36] = (DWORD)FrameStageNotifyThink;

	// Backup the original function from the untouched table.
	fnOriginalFunction = (FrameStageNotify)pOriginalClientDLLVMT[36];

	// Write the virtual method table.
	*pClientDLLVMT = pNewClientDLLVMT;

	// Import skins to use.
	SetSkinConfig();
	
	// Search for the 'CBaseViewModel' class.
	for (ClientClass* pClass = g_BaseClient->GetAllClasses(); pClass; pClass = pClass->m_pNext) {
		if (!strcmp(pClass->m_pNetworkName, "CBaseViewModel")) {
			// Search for the 'm_nModelIndex' property.
			RecvTable* pClassTable = pClass->m_pRecvTable;

			for (int nIndex = 0; nIndex < pClassTable->m_nProps; nIndex++) {
				RecvProp* pProp = &pClassTable->m_pProps[nIndex];

				if (!pProp || strcmp(pProp->m_pVarName, "m_nSequence"))
					continue;

				// Store the original proxy function.
				fnSequenceProxyFn = pProp->m_ProxyFn;

				// Replace the proxy function with our sequence changer.
				pProp->m_ProxyFn = (RecvVarProxyFn)SetViewModelSequence;

				break;
			}

			break;
		}
	}
}

bool __stdcall DllMain(HINSTANCE hDLLInstance, DWORD dwReason, LPVOID lpReserved) {
	if (dwReason == DLL_PROCESS_ATTACH)
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Initialise, 0, 0, 0);

	return true;
}