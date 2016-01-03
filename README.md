# Chameleon

### Description

Chameleon is a bare minimum internal skin & knife changer for Counter-Strike: Global Offensive.

Only the absolute essential classes and methods are implemented.

### Usage

* Clone or download from the archive link, extract and open in Visual Studio.
* Define your skin override information and viewmodel replacement indexes in `Skins.h`.
```
// Example to replace the default CT knife with a ★ Karambit | Fade.
inline void SetSkinConfig() {
	g_SkinChangerCfg[WEAPON_KNIFE].iItemDefinitionIndex = WEAPON_KNIFE_KARAMBIT;
	g_SkinChangerCfg[WEAPON_KNIFE].nFallbackPaintKit = 38;
	g_SkinChangerCfg[WEAPON_KNIFE].iEntityQuality = 3;
}
 
inline void SetModelConfig() {
	int nOriginalKnifeCT = g_ModelInfo->GetModelIndex("models/weapons/v_knife_default_ct.mdl");
	g_ViewModelCfg[nOriginalKnifeCT] = "models/weapons/v_knife_karam.mdl";
}

inline void SetKillIconCfg() {
	// Define replacement kill icons. (these only apply to you)
	g_KillIconCfg["knife_default_ct"] = "knife_karambit";
	g_KillIconCfg["knife_t"] = "knife_m9_bayonet";
}
```

* Compile and inject into `csgo.exe` using your preferred injector.

### Credits

Special thanks to:
- @AlvyPiper for teaching me how to do everything without the Source SDK.
- The UnKnoWnCheaTs CS:GO community for [their research](http://www.unknowncheats.me/forum/counterstrike-global-offensive/143458-csgo-skins-demystified-almost.html) on the subject.