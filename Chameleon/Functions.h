#pragma once

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
inline bool ApplyCustomModel(CBasePlayer* pLocal, CBaseAttributableItem* pWeapon) {
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
	pViewModel->SetModelIndex(g_ModelInfo->GetModelIndex(g_ViewModelCfg[nViewModelIndex]));

	return true;
}

// Function to apply custom kill icons to events.
inline bool ApplyCustomKillIcon(IGameEvent* pEvent) {
	// Get the user ID of the attacker.
	int nUserID = pEvent->GetInt("attacker");

	if (!nUserID)
		return false;

	// Only continue if we were the attacker.
	if (g_EngineClient->GetPlayerForUserID(nUserID) != g_EngineClient->GetLocalPlayer())
		return false;

	// Get the original weapon used to kill.
	const char* szWeapon = pEvent->GetString("weapon");

	for (auto ReplacementIcon: g_KillIconCfg) {
		// Search for a valid replacement.
		if (!strcmp(szWeapon, ReplacementIcon.first)) {
			// Replace with user defined value.
			pEvent->SetString("weapon", ReplacementIcon.second);
			break;
		}
	}

	return true;
}