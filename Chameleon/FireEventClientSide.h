#pragma once

// Define the calling convention for the FireEventClientSide function.
typedef bool(__thiscall *FireEventClientSide)(void*, IGameEvent*, char*);
FireEventClientSide fnOriginalFireEventClientSide = NULL;

// Perform kill icon replacements in here.
bool __fastcall FireEventClientSideThink(void* ecx, void* edx, IGameEvent* pEvent, char* unknown) {
	// If the event pointer is invalid just call the original.
	if (!pEvent)
		return fnOriginalFireEventClientSide(ecx, pEvent, unknown); 
	
	// Run our replacement function when a "player_death" event is fired.
	const char* szEventName = pEvent->GetName();

	if (!strcmp(szEventName, "player_death"))
		ApplyCustomKillIcon(pEvent);

	// Update model indexes when switching servers.
	if (!strcmp(szEventName, "player_connect")) {
		// Clear existing values.
		if (g_ViewModelCfg.size() >= 1)
			g_ViewModelCfg.clear();
		
		// Call SetModelConfig.
		SetModelConfig();
	}

	// Run the original FireEventClientSide function.
	return fnOriginalFireEventClientSide(ecx, pEvent, unknown);
};