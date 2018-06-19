#pragma once

class GlobalState
{
public:
	GlobalState();
	virtual ~GlobalState();

	// C++11 make class non-copyable
	GlobalState(const GlobalState&) = delete;
	GlobalState& operator=(const GlobalState&) = delete;

	void globalStart();
	void globalEnd();
	void globalTick(double deltaTime);
};