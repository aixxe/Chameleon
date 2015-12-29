#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Defines.h"
#include "DataTable.h"
#include "ClientClass.h"
#include "IClientEntity.h"
#include "IBaseClientDLL.h"
#include "IVEngineClient.h"
#include "IVModelInfoClient.h"
#include "IClientEntityList.h"

IBaseClientDLL* g_BaseClient = nullptr;
IVEngineClient* g_EngineClient = nullptr;
IClientEntityList* g_EntityList = nullptr;
IVModelInfoClient* g_ModelInfo = nullptr;