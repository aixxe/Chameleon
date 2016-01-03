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

// Include the "get replacement value" functions.
#include "Functions.h"

// Include the game function hooks.
#include "FrameStageNotify.h"
#include "FireEventClientSide.h"

void Initialise() {
	// Get the "CreateInterface" function from "client.dll" and "engine.dll".
	CreateInterfaceFn fnClientFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("client.dll"), "CreateInterface");
	CreateInterfaceFn fnEngineFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface");
	
	// Call "CreateInterface" to get the required class pointers.
	g_BaseClient = (IBaseClientDLL*)fnClientFactory("VClient017", NULL); 
	g_EntityList = (IClientEntityList*)fnClientFactory("VClientEntityList003", NULL);
	g_EngineClient = (IVEngineClient*)fnEngineFactory("VEngineClient013", NULL);
	g_ModelInfo = (IVModelInfoClient*)fnEngineFactory("VModelInfoClient004", NULL);
	g_GameEventMgr = (IGameEventManager2*)fnEngineFactory("GAMEEVENTSMANAGER002", NULL);
	
	// Get the virtual method tables for the classes we're going to hook from.
	PDWORD* pClientDLLVMT = (PDWORD*)g_BaseClient;
	PDWORD* pGameEventMgrVMT = (PDWORD*)g_GameEventMgr;

	// Save the untouched tables so we know where the original functions are.
	PDWORD pOriginalClientDLLVMT = *pClientDLLVMT;
	PDWORD pOriginalGameEventMgrVMT = *pGameEventMgrVMT;

	// Calculate the size of the tables.
	size_t dwClientDLLVMTSize = 0;
	size_t dwGameEventMgrVMTSize = 0;

	while ((PDWORD)(*pClientDLLVMT)[dwClientDLLVMTSize])
		dwClientDLLVMTSize++;

	while ((PDWORD)(*pGameEventMgrVMT)[dwGameEventMgrVMTSize])
		dwGameEventMgrVMTSize++;

	// Create the replacement tables.
	PDWORD pNewClientDLLVMT = new DWORD[dwClientDLLVMTSize];
	PDWORD pNewGameEventMgrVMT = new DWORD[dwGameEventMgrVMTSize];

	// Copy the original table into the replacement table.
	CopyMemory(pNewClientDLLVMT, pOriginalClientDLLVMT, (sizeof(DWORD) * dwClientDLLVMTSize));
	CopyMemory(pNewGameEventMgrVMT, pOriginalGameEventMgrVMT, (sizeof(DWORD) * dwGameEventMgrVMTSize));

	// Change the FrameStageNotify function in the new table to point to our function.
	pNewClientDLLVMT[36] = (DWORD)FrameStageNotifyThink;
	
	// Change the FireEventClientSide function in the new table to point to our function.
	pNewGameEventMgrVMT[8] = (DWORD)FireEventClientSideThink;

	// Backup the original function from the untouched tables.
	fnOriginalFrameStageNotify = (FrameStageNotify)pOriginalClientDLLVMT[36];
	fnOriginalFireEventClientSide = (FireEventClientSide)pOriginalGameEventMgrVMT[8];

	// Write the virtual method tables.
	*pClientDLLVMT = pNewClientDLLVMT;
	*pGameEventMgrVMT = pNewGameEventMgrVMT;

	// Import skins to use.
	SetSkinConfig();

	// Import replacement kill icons.
	SetKillIconCfg();
	
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