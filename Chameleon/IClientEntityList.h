#pragma once

class IClientEntityList {
	public:
		inline IClientEntity* GetClientEntity(int Index) {
			return GetVirtualFunction<IClientEntity*(__thiscall *)(void *, int)>(this, 3)(this, Index);
		}

		inline IClientEntity* GetClientEntityFromHandle(DWORD Handle) {
			return GetVirtualFunction<IClientEntity*(__thiscall *)(void *, int)>(this, 4)(this, Handle);
		}
};