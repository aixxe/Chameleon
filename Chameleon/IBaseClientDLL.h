#pragma once

class IBaseClientDLL {
	public:
		inline ClientClass* GetAllClasses() {
			return CallVirtualFunction<ClientClass*(__thiscall *)(void*)>(this, 8)(this);
		}
};