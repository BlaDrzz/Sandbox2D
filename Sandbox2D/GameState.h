#pragma once

struct Graphics;

class GameState 
{
public:
	GameState()
	{
		// nothing to create
	}

	virtual ~GameState()
	{
		// nothing to destroy
	}

	// C++11 make the class non-copyable
	GameState(const GameState&) = delete;
	GameState& operator=(const GameState&) = delete;

	virtual void stateStart() = 0;
	virtual void stateEnd() = 0;
	virtual void stateTick(double) = 0;
	virtual void statePaint(Graphics*) = 0;
};