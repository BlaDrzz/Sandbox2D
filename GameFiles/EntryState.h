#pragma once

// Include files
#include "../Sandbox2D/GameState.h"

// Forward Declarations

// EntryState class
class EntryState : public GameState
{
public:
	// Constructor
	EntryState();
	virtual ~EntryState();

	// C++11 make class non-copyable
	EntryState(const EntryState&) = delete;
	EntryState& operator=(const EntryState&) = delete;

	// General Methods
	void stateStart() override;
	void stateEnd() override;
	void stateTick(double deltaTime) override;
	void statePaint(Graphics* g) override;

private:
	// Private functions

	// Datamembers
	ButtonWidget* _btnSwitchToPhysics = nullptr;
	ButtonWidget* _btnSwitchToAudio = nullptr;
};