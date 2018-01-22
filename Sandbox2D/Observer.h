#pragma once
#include "Any.h"

struct Event
{
	std::string _flag;
	Any::Any _payload;
};

/* This struct listens for Events */
struct Listener
{
	std::string _flag;
	std::function<void(Event)> _callback;
};

/* This struct handles Listeners */
struct Observer
{
	std::vector<Listener> _listeners;
};

inline void Emit(Observer* ob, const Event evt, const std::function<void(Any::Any)>& deleter)
{
	for (const auto& listener : ob->_listeners )
	{
		if (listener._flag == evt._flag)
		{
			listener._callback(evt);
		}
	}

	deleter(evt._payload);
}

inline void On(Observer* ob, const std::string& flag, const std::function<void(Event)>& callback)
{
	ob->_listeners.push_back({
		flag,
		callback
	});
}
