#pragma once

class IBaseClientDLL {
	public:
		inline ClientClass* GetAllClasses() {
			return GetVirtualFunction<ClientClass*(__thiscall *)(void*)>(this, 8)(this);
		}
};