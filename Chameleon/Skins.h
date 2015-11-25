#pragma once

#include <unordered_map>

struct EconomyItemCfg {
	int nFallbackPaintKit = 0;
	int nFallbackSeed = 0;
	int nFallbackStatTrak = -1;
	int iEntityQuality = 4;
	char* szCustomName = nullptr;
	float flFallbackWear = 0.1f;
};

std::unordered_map<int, EconomyItemCfg> g_SkinChangerCfg;

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
}