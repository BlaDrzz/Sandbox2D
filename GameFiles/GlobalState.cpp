// +-----------------------------------------------------------------------------------------------+
// | THE ENGINE REQUIRES THIS STATE TO EXIST!!   DO NOT REMOVE UNLESS YOU KNOW WHAT YOU'RE DOING!! |
// +-----------------------------------------------------------------------------------------------+

// Include files
#include "../stdafx.h"
#include "GlobalState.h"

// Defines
#define S2D (Sandbox2D::GetSingleton())

// GlobalState methods
GlobalState::GlobalState() {}
GlobalState::~GlobalState() {}

void GlobalState::globalStart()
{
	// Executed at beginning of the game
}

void GlobalState::globalEnd()
{
	// Executed at end of the game
}

void GlobalState::globalTick(double deltaTime)
{
	// Executed before the active state's stateTick
}