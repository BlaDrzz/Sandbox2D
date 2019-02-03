#pragma once

// Include files
#include "../Sandbox2D/GameState.h"

// Forward Declarations
class WorldMap;
class PlayerController;

// PlayState class
class PlayState : public GameState
{
public:
	// Constructor
	PlayState() = default;
	virtual ~PlayState() = default;

	// C++11 make class non-copyable
	PlayState(const PlayState&) = delete;
	PlayState& operator=(const PlayState&) = delete;

	// General Methods
	void stateStart() override;
	void stateEnd() override;
	void stateTick(double deltaTime) override;
	void statePaint(Graphics* g) override;

private:
	// Private functions

	// Datamembers
	ButtonWidget* _btnBack = nullptr;
	WorldMap* _worldMap = nullptr;
	PlayerController* _playerController = nullptr;
};