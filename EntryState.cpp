#pragma once

// Include files
#include "stdafx.h"
#include "EntryState.h"
#include "TestState.h"

// Defines
#define S2D (Sandbox2D::GetSingleton())

// EntryState methods
EntryState::EntryState() {}
EntryState::~EntryState() {}

void EntryState::stateStart()
{
	// Executed at start of state
	_btnTestState = new ButtonWidget({ 10,10 });
	_btnTestState->_text = "Switch to test state";
	_btnTestState->_backColor = { 0, 255, 0, 255 };
	_btnTestState->_fontColor = { 0, 0, 0, 255 };
	_btnTestState->_textPadding = { 10, 10, 10, 10 };
	
}

void EntryState::stateEnd()
{
	// Executed at end of state
	delete _btnTestState;
}

void EntryState::stateTick(double deltaTime) 
{
	// Executed each game tick, game logic goes here
	if (_btnTestState->isPressed())
	{
		S2D->changeState(new TestState());
	}
}

void EntryState::statePaint(Graphics* g)
{
	// Executed after game tick, game drawing calls go 
	_btnTestState->draw();
}	