#ifndef EFFECTS_HOOK_H
#define EFFECTS_HOOK_H

typedef struct
{
	ClientEffectCallback hook;
	unsigned int hash;
	ClientEffectCallback original;
} EffectHook;

namespace EffectsHook
{
	inline void HookAll(EffectHook* hooks, size_t size, CClientEffectRegistration* reg)
	{
		while(reg) {
			unsigned int hash = Crc32((char*)reg->m_pEffectName, strlen(reg->m_pEffectName));
			for (size_t i = 0; i < size; i++) {
				if (hooks[i].hash == hash) {
					hooks[i].original = reg->m_pFunction;
					reg->m_pFunction = hooks[i].hook;
				}
			}
			reg = reg->m_pNext;
		}
	}

	inline void UnhookAll(EffectHook* hooks, size_t size, CClientEffectRegistration* reg)
	{
		while(reg) {
			for (size_t i = 0; i < size; i++) {
				if (hooks[i].hook == reg->m_pFunction)
					reg->m_pFunction = hooks[i].original;
			}
			reg = reg->m_pNext;
		}
	}

	inline ClientEffectCallback GetOriginalCallback(EffectHook* hooks, size_t size, ClientEffectCallback func)
	{
		for (size_t i = 0; i < size; i++)
			if (hooks[i].hook == func)
				return hooks[i].original;
		return nullptr;
	}
}

#endif
