#pragma once

class IVModelInfoClient {
	public:
		inline void* GetModel(int Index) {
			return GetVirtualFunction<void*(__thiscall *)(void*, int)>(this, 1)(this, Index);
		}

		inline int GetModelIndex(const char* Filename) {
			return GetVirtualFunction<int(__thiscall *)(void*, const char*)>(this, 2)(this, Filename);
		}

		inline const char* GetModelName(const void* Model) {
			return GetVirtualFunction<const char*(__thiscall *)(void*, const void*)>(this, 3)(this, Model);
		}
};