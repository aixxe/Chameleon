#pragma once

// Define the calling convention for the FireEventClientSide function.
typedef bool(__thiscall *FireEventClientSide)(void*, IGameEvent*);
FireEventClientSide fnOriginalFireEventClientSide = NULL;

// Perform kill icon replacements in here.
void __fastcall FireEventClientSideThink(void* ecx, void* edx, IGameEvent* pEvent) {
	// Run our replacement function when a "player_death" event is fired.
	if (pEvent && !strcmp(pEvent->GetName(), "player_death"))
		ApplyCustomKillIcon(pEvent);

	// Run the original FireEventClientSide function.
	fnOriginalFireEventClientSide(ecx, pEvent);
};