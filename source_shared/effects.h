#ifndef SOURCE_EFFECTS_H
#define SOURCE_EFFECTS_H

struct CEffectData
{
	vec3 origin;
	vec3 start;
	vec3 normal;
	vec3 angles;
	int flags;
	int entity;
	float scale;
	float magnitude;
	float radius;
	int attachmentIndex;
	short surfaceProp;

	int material;
	int damageType;
	int hitBox;

	int otherEntIndex;

	unsigned char color;

	//bool positionsAreRelativeToEntity;

	int effectName;

	CEffectData()
	{
		origin = vec3();
		start = vec3();
		normal = vec3();
		angles = vec3();

		flags = 0;
		entity = -1;
		scale = 1.f;
		attachmentIndex = 0;
		surfaceProp = 0;

		magnitude = 0.0f;
		radius = 0.0f;

		material = 0;
		damageType = 0;
		hitBox = 0;

		color = 0;

		otherEntIndex = 0;

		//positionsAreRelativeToEntity = false;
	}

	int GetEffectNameIndex() { return effectName; }

	C_BaseEntity* GetEntity() const;
	int entindex() const;
};

typedef void (*ClientEffectCallback)(const CEffectData& data);

struct CClientEffectRegistration
{
  public:
	CClientEffectRegistration(const char* pEffectName, ClientEffectCallback fn);

  public:
	const char* effectName;
	ClientEffectCallback function;
	CClientEffectRegistration* next;

	static CClientEffectRegistration* head;
};


#endif
