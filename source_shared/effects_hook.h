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
			unsigned int hash = Crc32((char*)reg->effectName, strlen(reg->effectName));
			for (size_t i = 0; i < size; i++) {
				if (hooks[i].hash == hash) {
					hooks[i].original = reg->function;
					reg->function = hooks[i].hook;
				}
			}
			reg = reg->next;
		}
	}

	inline void UnhookAll(EffectHook* hooks, size_t size, CClientEffectRegistration* reg)
	{
		while(reg) {
			for (size_t i = 0; i < size; i++) {
				if (hooks[i].hook == reg->function)
					reg->function = hooks[i].original;
			}
			reg = reg->next;
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
