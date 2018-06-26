#ifndef SOURCE_EFFECTS_H
#define SOURCE_EFFECTS_H

struct CEffectData
{
	vec3 m_vOrigin;
	vec3 m_vStart;
	vec3 m_vNormal;
	vec3 m_vAngles;
	int flags;
	int m_hEntity;
	float m_flScale;
	float m_flMagnitude;
	float m_flRadius;
	int m_nAttachmentIndex;
	short m_nSurfaceProp;

	int m_nMaterial;
	int m_nDamageType;
	int m_nHitBox;

	int m_nOtherEntIndex;

	unsigned char m_nColor;

	//bool m_bPositionsAreRelativeToEntity;

	int m_iEffectName;

	CEffectData()
	{
		m_vOrigin = vec3();
		m_vStart = vec3();
		m_vNormal = vec3();
		m_vAngles = vec3();

		flags = 0;
		m_hEntity = -1;
		m_flScale = 1.f;
		m_nAttachmentIndex = 0;
		m_nSurfaceProp = 0;

		m_flMagnitude = 0.0f;
		m_flRadius = 0.0f;

		m_nMaterial = 0;
		m_nDamageType = 0;
		m_nHitBox = 0;

		m_nColor = 0;

		m_nOtherEntIndex = 0;

		//m_bPositionsAreRelativeToEntity = false;
	}

	int GetEffectNameIndex() { return m_iEffectName; }

	C_BaseEntity* GetEntity() const;
	int entindex() const;
};

typedef void (*ClientEffectCallback)(const CEffectData &data);

struct CClientEffectRegistration
{
  public:
	CClientEffectRegistration(const char *pEffectName, ClientEffectCallback fn);

  public:
	const char* m_pEffectName;
	ClientEffectCallback m_pFunction;
	CClientEffectRegistration* m_pNext;

	static CClientEffectRegistration* s_pHead;
};


#endif
