#ifndef GLOW_OBJECT_MANAGER_H
#define GLOW_OBJECT_MANAGER_H

struct GlowObjectDefinition_t;

enum GlowSlotValue : int {
	END_OF_FREE_LIST = -1,
	ENTRY_IN_USE = -2
};

class CGlowObjectManager
{
public:

	int RegisterGlowObject(const GlowObjectDefinition_t& def)
	{
		int index;

		if (firstFreeSlot == GlowSlotValue::END_OF_FREE_LIST)
			index = glowObjectDefinitions.AddToTail();
		else {
			index = firstFreeSlot;
			firstFreeSlot = glowObjectDefinitions[index].nextFreeSlot;
		}

		glowObjectDefinitions[index] = def;
		glowObjectDefinitions[index].nextFreeSlot = GlowSlotValue::ENTRY_IN_USE;

		return index;
	}

	int RegisterGlowObject(IHandleEntity* ent)
	{
		GlowObjectDefinition_t def;
		def.ent = decltype(glowObjectDefinitions[0].ent)(ent);
		return RegisterGlowObject(def);
	}

	void UnregisterGlowObject(int index)
	{
		glowObjectDefinitions[index].nextFreeSlot = firstFreeSlot;
		glowObjectDefinitions[index].ent = decltype(glowObjectDefinitions[index].ent)();
		firstFreeSlot = index;
	}

	bool IsSlotInUse(int index)
	{
		return glowObjectDefinitions[index].nextFreeSlot == GlowSlotValue::ENTRY_IN_USE;
	}

	int GetDefinitionIndex(IHandleEntity* ent)
	{
		for (int i = 0; i < glowObjectDefinitions.Count(); i++)
			if (IsSlotInUse(i) && glowObjectDefinitions[i].ent == ent)
				return i;

		return -1;
	}

	CUtlVector<GlowObjectDefinition_t> glowObjectDefinitions;
	int firstFreeSlot;
};


#endif