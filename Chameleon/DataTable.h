#pragma once

struct RecvProp;

struct DVariant {
	union {
		float m_Float;
		long m_Int;
		char* m_pString;
		void* m_pData;
		float m_Vector[3];
		__int64 m_Int64;
	};

	int	m_Type;
};

struct CRecvProxyData {
	const RecvProp* m_pRecvProp;
	DVariant m_Value;
	int m_iElement;
	int m_ObjectID;
};

struct RecvTable {
	public:
		RecvProp* m_pProps;
		int m_nProps;
		void* m_pDecoder;
		char* m_pNetTableName;
	private:
		char pad00[2];
};

typedef void(__cdecl *RecvVarProxyFn)(const CRecvProxyData*, void*, void*);

struct RecvProp {
	char* m_pVarName;
	int m_RecvType;
	int m_Flags;
	int m_StringBufferSize;
	bool m_bInsideArray;
	const void* m_pExtraData;
	RecvProp* m_pArrayProp;
	void* m_ArrayLengthProxy;
	RecvVarProxyFn m_ProxyFn;
	void* m_DataTableProxyFn;
	RecvTable* m_pDataTable;
	int m_Offset;
	int m_ElementStride;
	int m_nElements;
	const char* m_pParentArrayPropName;
};