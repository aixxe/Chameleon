#pragma once

class IGameEvent {
	public:
		const char* GetName() {
			return GetVirtualFunction<const char*(__thiscall *)(void*)>(this, 1)(this);
		}

		int GetInt(const char* szKeyName, int nDefault = 0) {
			return GetVirtualFunction<int(__thiscall *)(void*, const char*, int)>(this, 6)(this, szKeyName, nDefault);
		}

		const char* GetString(const char* szKeyName) {
			return GetVirtualFunction<const char*(__thiscall *)(void*, const char*, int)>(this, 9)(this, szKeyName, 0);
		}

		void SetString(const char* szKeyName, const char* szValue) {
			return GetVirtualFunction<void(__thiscall *)(void*, const char*, const char*)>(this, 16)(this, szKeyName, szValue);
		}
};

class IGameEventManager2 {};