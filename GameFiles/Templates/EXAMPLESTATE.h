#pragma once

// Include files
#include "../Sandbox2D/GameState.h"

// Forward Declarations

// EXAMPLESTATE class
class EXAMPLESTATE : public GameState
{
public:
	// Constructor
	EXAMPLESTATE();
	virtual ~EXAMPLESTATE();

	// C++11 make class non-copyable
	EXAMPLESTATE(const EXAMPLESTATE&) = delete;
	EXAMPLESTATE& operator=(const EXAMPLESTATE&) = delete;

	// General Methods
	void stateStart() override;
	void stateEnd() override;
	void stateTick(double deltaTime) override;
	void statePaint(Graphics* g) override;

private:
	// Private functions

	// Datamembers
};