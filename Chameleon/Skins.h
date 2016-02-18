#pragma once

#include <unordered_map>

struct EconomyItemCfg {
	int iItemDefinitionIndex = 0;
	int nFallbackPaintKit = 0;
	int nFallbackSeed = 0;
	int nFallbackStatTrak = -1;
	int iEntityQuality = 4;
	char* szCustomName = nullptr;
	float flFallbackWear = 0.1f;
};

std::unordered_map<int, EconomyItemCfg> g_SkinChangerCfg;
std::unordered_map<int, const char*> g_ViewModelCfg;
std::unordered_map<const char*, const char*> g_KillIconCfg;

inline void SetSkinConfig() {
	// StatTrak™ AWP | Dragon Lore
	g_SkinChangerCfg[WEAPON_AWP].nFallbackPaintKit = 344;
	g_SkinChangerCfg[WEAPON_AWP].flFallbackWear = 0.00000001f;
	g_SkinChangerCfg[WEAPON_AWP].nFallbackStatTrak = 1337;

	// Valve AK-47 | Redline
	g_SkinChangerCfg[WEAPON_AK47].nFallbackPaintKit = 282;
	g_SkinChangerCfg[WEAPON_AK47].iEntityQuality = 6;

	// Souvenir M4A4 | Howl
	g_SkinChangerCfg[WEAPON_M4A1].nFallbackPaintKit = 309;
	g_SkinChangerCfg[WEAPON_M4A1].iEntityQuality = 12;

	// Prototype Desert Eagle | Conspiracy
	g_SkinChangerCfg[WEAPON_DEAGLE].nFallbackPaintKit = 351;
	g_SkinChangerCfg[WEAPON_DEAGLE].iEntityQuality = 7;

	// Glock-18 | Fade
	g_SkinChangerCfg[WEAPON_GLOCK].nFallbackPaintKit = 38;

	// USP-S | Stainless
	g_SkinChangerCfg[WEAPON_USP_SILENCER].nFallbackPaintKit = 277;

	// Karambit | Fade (CT)
	g_SkinChangerCfg[WEAPON_KNIFE].iItemDefinitionIndex = WEAPON_KNIFE_KARAMBIT;
	g_SkinChangerCfg[WEAPON_KNIFE].nFallbackPaintKit = 38;
	g_SkinChangerCfg[WEAPON_KNIFE].iEntityQuality = 3;

	// Bowie Knife | Crimson Web (T)
	g_SkinChangerCfg[WEAPON_KNIFE_T].iItemDefinitionIndex = WEAPON_KNIFE_SURVIVAL_BOWIE;
	g_SkinChangerCfg[WEAPON_KNIFE_T].nFallbackPaintKit = 12;
	g_SkinChangerCfg[WEAPON_KNIFE_T].iEntityQuality = 3;
}

inline void SetModelConfig() {
	// Get the indexes of the models we want to replace.
	int nOriginalKnifeCT = g_ModelInfo->GetModelIndex("models/weapons/v_knife_default_ct.mdl");
	int nOriginalKnifeT = g_ModelInfo->GetModelIndex("models/weapons/v_knife_default_t.mdl");

	// Configure model replacements.
	g_ViewModelCfg[nOriginalKnifeCT] = "models/weapons/v_knife_karam.mdl";
	g_ViewModelCfg[nOriginalKnifeT] = "models/weapons/v_knife_survival_bowie.mdl";
}

inline void SetKillIconCfg() {
	// Define replacement kill icons. (these only apply to you)
	g_KillIconCfg["knife_default_ct"] = "knife_karambit";
	g_KillIconCfg["knife_t"] = "knife_survival_bowie";
}