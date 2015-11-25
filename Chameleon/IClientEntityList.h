#pragma once

class IClientEntityList {
	public:
		inline IClientEntity* GetClientEntity(int Index) {
			return CallVirtualFunction<IClientEntity*(__thiscall *)(void *, int)>(this, 3)(this, Index);
		}

		inline IClientEntity* GetClientEntityFromHandle(DWORD Handle) {
			return CallVirtualFunction<IClientEntity*(__thiscall *)(void *, int)>(this, 4)(this, Handle);
			//return this->GetClientEntity(Handle & 0xFFFF);
		}
};