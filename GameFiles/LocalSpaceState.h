#pragma once

// Include files
#include "../Sandbox2D/GameState.h"

// Forward Declarations
class PlayerController;

// LocalSpaceState class
class LocalSpaceState : public GameState
{
public:
	// Constructor
	LocalSpaceState();
	virtual ~LocalSpaceState();

	// C++11 make class non-copyable
	LocalSpaceState(const LocalSpaceState&) = delete;
	LocalSpaceState& operator=(const LocalSpaceState&) = delete;

	// General Methods
	void stateStart() override;
	void stateEnd() override;
	void stateTick(double deltaTime) override;
	void statePaint(Graphics* g) override;

private:
	// Private functions

	// Datamembers
	PlayerController* _player = nullptr;
};