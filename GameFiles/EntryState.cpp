// +-----------------------------------------------------------------------------------------------+
// | THE ENGINE USES THIS STATE AS ENTRY POINT!! DO NOT REMOVE UNLESS YOU KNOW WHAT YOU'RE DOING!! |
// +-----------------------------------------------------------------------------------------------+

// Include files
#include "../stdafx.h"
#include "EntryState.h"

// Defines
#define S2D (Sandbox2D::GetSingleton())

// EntryState methods
EntryState::EntryState() {}
EntryState::~EntryState() {}

void EntryState::stateStart()
{
	// Executed at start of state
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
	g->drawLine({ 0,0 }, { 100,100 });
}