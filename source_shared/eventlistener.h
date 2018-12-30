#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include "../framework/utils/crc32.h"

class IGameEventListener;
class IGameEventManager;

template <typename T, size_t N>
class EventListener : IGameEventListener
{
	T fptrs[N];
  public:
	bool initialized;

	EventListener(const T (&funcs)[N])
	{
		initialized = false;
		for (size_t i = 0; i < N; i++)
			fptrs[i] = funcs[i];
	}

	void AddListener(const char* event)
	{
		gameEvents->AddListener(this, event, false);
	}

	template<typename... Args>
	void AddListener(const char* event, Args... events)
	{
		AddListener(event);
		AddListener(events...);
	}

	template<typename... Args>
	void Initialize(Args... events)
	{
		AddListener(events...);
		initialized = true;
	}

	~EventListener()
	{
		if (initialized)
			gameEvents->RemoveListener(this);
	}

	void FireGameEvent(IGameEvent* event) override
	{
		const char* name = event->GetName();
		unsigned int crc = 0;

		if (name)
			crc = Crc32((char*)name, strlen(name));

		for (size_t i = 0; i < N; i++)
			fptrs[i](event, crc);
	}

	int GetEventDebugID() override
	{
		return 42;
	}
};

#endif
