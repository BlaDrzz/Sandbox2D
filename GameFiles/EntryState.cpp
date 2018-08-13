// +-----------------------------------------------------------------------------------------------+
// | THE ENGINE USES THIS STATE AS ENTRY POINT!! DO NOT REMOVE UNLESS YOU KNOW WHAT YOU'RE DOING!! |
// +-----------------------------------------------------------------------------------------------+

// Include files
#include "../stdafx.h"
#include "EntryState.h"
#include "LocalSpaceState.h"

// Defines
#define S2D (Sandbox2D::GetSingleton())

// EntryState methods
EntryState::EntryState() {}
EntryState::~EntryState() {}

void EntryState::stateStart()
{
	// Executed at start of state
	S2D->pushState(new LocalSpaceState());
}

void EntryState::stateEnd()
{
}

void EntryState::stateTick(double deltaTime) 
{
	// Executed each game tick, game logic goes here
}

void EntryState::statePaint(Graphics* g)
{
	// Executed after game tick, game drawing calls go 
}