#pragma once

class IVEngineClient {
	public:
		inline int GetLocalPlayer() {
			return CallVirtualFunction<int(__thiscall *)(void *)>(this, 12)(this);
		}
};