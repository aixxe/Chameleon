#pragma once

class ClientClass {
	private:
		char __pad[0x8];
	public:
		char* m_pNetworkName;
		RecvTable* m_pRecvTable;
		ClientClass* m_pNext;
		int m_ClassID;
};