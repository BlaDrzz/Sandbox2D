#pragma once

// Include files
#include "stdafx.h"
#include "TestState.h"

// Defines
#define S2D (Sandbox2D::GetSingleton())

// StateWithWidgets methods
TestState::TestState() {}
TestState::~TestState() {}

void TestState::stateStart()
{
	// Executed at start of state
}

void TestState::stateEnd()
{
	// Executed at end of state
}

void TestState::stateTick(double deltaTime)
{
	// Executed each game tick, game logic goes here
}

void TestState::statePaint(Graphics* g)
{
	// Executed after game tick, game drawing calls go 
}	