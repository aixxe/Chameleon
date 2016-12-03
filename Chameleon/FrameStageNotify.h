#pragma once

// Define the calling convention for the FrameStageNotify function.
typedef void(__thiscall *FrameStageNotify)(void*, ClientFrameStage_t);
FrameStageNotify fnOriginalFrameStageNotify = NULL;

void __fastcall FrameStageNotifyThink(void* ecx, void* edx, ClientFrameStage_t Stage) {
	while (Stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
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

			// Set the replacement model on the weapon (to get around the 29 Nov 2016 update check)
			if (g_ViewModelCfg.find(pWeapon->GetModelIndex()) != g_ViewModelCfg.end())
				pWeapon->SetModelIndex(g_ModelInfo->GetModelIndex(g_ViewModelCfg[pWeapon->GetModelIndex()]));
			
			ApplyCustomModel(pLocal, pWeapon);

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
	fnOriginalFrameStageNotify(ecx, Stage);
}