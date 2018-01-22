#pragma once

// Include files
#include "Sandbox2D/GameState.h"

// Forward Declarations

// StateWithWidgets class
class TestState : public GameState
{
public:
	// Constructor
	TestState();
	virtual ~TestState();

	// C++11 make class non-copyable
	TestState(const TestState&) = delete;
	TestState& operator=(const TestState&) = delete;

	// General Methods
	void stateStart() override;
	void stateEnd() override;
	void stateTick(double deltaTime) override;
	void statePaint(Graphics* g) override;

private:
	// Private functions

	// Datamembers
};