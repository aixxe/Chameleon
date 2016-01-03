#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class IBaseClientDLL;
class IVEngineClient;
class IClientEntityList;
class IVModelInfoClient;
class IGameEventManager2;
class IClientEntity;

IBaseClientDLL* g_BaseClient = nullptr;
IVEngineClient* g_EngineClient = nullptr;
IClientEntityList* g_EntityList = nullptr;
IVModelInfoClient* g_ModelInfo = nullptr;
IGameEventManager2* g_GameEventMgr = nullptr;

#include "Defines.h"
#include "DataTable.h"
#include "ClientClass.h"
#include "IBaseClientDLL.h"
#include "IVEngineClient.h"
#include "IVModelInfoClient.h"
#include "IGameEvents.h"
#include "IClientEntityList.h"
#include "IClientEntity.h"