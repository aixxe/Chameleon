#pragma once

class IClientEntity {
	public:
		inline BYTE GetLifeState() {
			// DT_BasePlayer -> m_lifeState: 0x25B
			return *(BYTE*)((DWORD)this + 0x25B);
		}

		inline UINT* GetWeapons() {
			// DT_BasePlayer -> m_hMyWeapons: 0x2DC8
			return (UINT*)((DWORD)this + 0x2DC8);
		}
};

class CBaseAttributableItem: IClientEntity {
	public:
		inline int* GetItemDefinitionIndex() {
			// DT_BaseAttributableItem -> m_AttributeManager: 0x2D50
			// DT_BaseAttributableItem -> m_AttributeManager -> m_Item: 0x40
			// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iItemDefinitionIndex: 0x1D0
			return (int*)((DWORD)this + 0x2D50 + 0x40 + 0x1D0);
		}

		inline int* GetItemIDHigh() {
			// DT_BaseAttributableItem -> m_AttributeManager: 0x2D50
			// DT_BaseAttributableItem -> m_AttributeManager -> m_Item: 0x40
			// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iItemIDHigh: 0x1E8
			return (int*)((DWORD)this + 0x2D50 + 0x40 + 0x1E8);
		}
	
		inline int* GetEntityQuality() {
			// DT_BaseAttributableItem -> m_AttributeManager: 0x2D50
			// DT_BaseAttributableItem -> m_AttributeManager -> m_Item: 0x40
			// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iEntityQuality: 0x1D4
			return (int*)((DWORD)this + 0x2D50 + 0x40 + 0x1D4);
		}

		inline char* GetCustomName() {
			// DT_BaseAttributableItem -> m_AttributeManager: 0x2D50
			// DT_BaseAttributableItem -> m_AttributeManager -> m_Item: 0x40
			// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_szCustomName: 0x264
			return (char*)((DWORD)this + 0x2D50 + 0x40 + 0x264);
		}

		inline int* GetFallbackPaintKit() {
			// DT_BaseAttributableItem -> m_nFallbackPaintKit: 0x3140
			return (int*)((DWORD)this + 0x3140);
		}

		inline int* GetFallbackSeed() {
			// DT_BaseAttributableItem -> m_nFallbackSeed: 0x3144
			return (int*)((DWORD)this + 0x3144);
		}

		inline float* GetFallbackWear() {
			// DT_BaseAttributableItem -> m_flFallbackWear: 0x3148
			return (float*)((DWORD)this + 0x3148);
		}

		inline int* GetFallbackStatTrak() {
			// DT_BaseAttributableItem -> m_nFallbackStatTrak: 0x314C
			return (int*)((DWORD)this + 0x314C);
		}
};