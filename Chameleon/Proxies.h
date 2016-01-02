#pragma once

// Store the original proxy functions.
RecvVarProxyFn fnModelIndexProxyFn = NULL;
RecvVarProxyFn fnSequenceProxyFn = NULL;

// Function to change viewmodels.
void SetViewModelIndex(const CRecvProxyData *pDataConst, void *pStruct, void *pOut) {
	// Ensure the model replacements are available. (called here so GetModelIndex returns valid IDs)
	if (g_ViewModelCfg.size() == 0)
		SetModelConfig();

	// Make the incoming data editable.
	CRecvProxyData* pData = const_cast<CRecvProxyData*>(pDataConst);

	// Check for a model replacement in the global table.
	if (g_ViewModelCfg.find(pData->m_Value.m_Int) != g_ViewModelCfg.end()) {
		// Confirm that we are replacing our view model and not someone elses.
		CBaseViewModel* pViewModel = (CBaseViewModel*)pStruct;

		if (pViewModel) {
			// Compare the owner entity of this view model to the local player entity.
			IClientEntity* pLocal = g_EntityList->GetClientEntity(g_EngineClient->GetLocalPlayer());

			if (pLocal == g_EntityList->GetClientEntityFromHandle(pViewModel->GetOwner())) {
				// Replace the view model with the user defined value.
				pData->m_Value.m_Int = g_ViewModelCfg[pData->m_Value.m_Int];
			}
		}
	}

	// Call original function with the modified data.
	fnModelIndexProxyFn(pData, pStruct, pOut);
}

// Function to fix sequences for certain models.
void SetViewModelSequence(const CRecvProxyData *pDataConst, void *pStruct, void *pOut) {
	// Make the incoming data editable.
	CRecvProxyData* pData = const_cast<CRecvProxyData*>(pDataConst);

	// Confirm that we are replacing our view model and not someone elses.
	CBaseViewModel* pViewModel = (CBaseViewModel*)pStruct;

	// Compare the owner entity of this view model to the local player entity.
	IClientEntity* pLocal = g_EntityList->GetClientEntity(g_EngineClient->GetLocalPlayer());

	if (pLocal == g_EntityList->GetClientEntityFromHandle(pViewModel->GetOwner())) {
		// Get the filename of the current view model.
		void* pModel = g_ModelInfo->GetModel(*pViewModel->GetModelIndex());
		const char* szModel = g_ModelInfo->GetModelName(pModel);

		// Store the current sequence.
		int m_nSequence = pData->m_Value.m_Int;

		if (!strcmp(szModel, "models/weapons/v_knife_butterfly.mdl")) {
			// Fix animations for the Butterfly Knife.
			switch (m_nSequence) {
				case SEQUENCE_DEFAULT_DRAW:
					m_nSequence = RandomInt(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2); break;
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence = RandomInt(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03); break;
				default:
					m_nSequence++;
			}
		} else if (!strcmp(szModel, "models/weapons/v_knife_falchion_advanced.mdl")) {
			// Fix animations for the Falchion Knife.
			switch (m_nSequence) {
				case SEQUENCE_DEFAULT_IDLE2:
					m_nSequence = SEQUENCE_FALCHION_IDLE1; break;
				case SEQUENCE_DEFAULT_HEAVY_MISS1:
					m_nSequence = RandomInt(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP); break;
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence = RandomInt(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02); break;
				case SEQUENCE_DEFAULT_DRAW:
				case SEQUENCE_DEFAULT_IDLE1:
					break;
				default:
					m_nSequence--;
			}
		} else if (!strcmp(szModel, "models/weapons/v_knife_push.mdl")) {
			// Fix animations for the Shadow Daggers.
			switch (m_nSequence) {
				case SEQUENCE_DEFAULT_IDLE2:
					m_nSequence = SEQUENCE_DAGGERS_IDLE1; break;
				case SEQUENCE_DEFAULT_LIGHT_MISS1:
				case SEQUENCE_DEFAULT_LIGHT_MISS2:
					m_nSequence = RandomInt(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5); break;
				case SEQUENCE_DEFAULT_HEAVY_MISS1:
					m_nSequence = RandomInt(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1); break;
				case SEQUENCE_DEFAULT_HEAVY_HIT1:
				case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence += 3; break;
				case SEQUENCE_DEFAULT_DRAW:
				case SEQUENCE_DEFAULT_IDLE1:
					break;
				default:
					m_nSequence += 2;
			}
		}

		// Set the fixed sequence.
		pData->m_Value.m_Int = m_nSequence;
	}

	// Call original function with the modified data.
	fnSequenceProxyFn(pData, pStruct, pOut);
}