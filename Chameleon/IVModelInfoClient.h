#pragma once

class IVModelInfoClient {
	public:
		inline int GetModelIndex(const char* Filename) {
			return CallVirtualFunction<int(__thiscall *)(void*, const char*)>(this, 2)(this, Filename);
		}
};