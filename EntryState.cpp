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
	_lblInfo = new LabelWidget("Press E key to fire the event.", { 10,10 });
	
	_btnTestState = new ButtonWidget({ 10,30 });
	_btnTestState->_text = "Observer present";
	_btnTestState->_backColor = { 0, 255, 0, 255 };
	_btnTestState->_fontColor = { 0, 0, 0, 255 };
	_btnTestState->_textPadding = { 10, 10, 10, 10 };
}

void EntryState::stateEnd()
{
	// Executed at end of state
	delete _btnTestState;
	delete _lblInfo;
	
}

void EntryState::stateTick(double deltaTime) 
{
	// Executed each game tick, game logic goes here
}

void EntryState::statePaint(Graphics* g)
{
	// Executed after game tick, game drawing calls go 
	_lblInfo->draw();
	_btnTestState->draw();
	if (_btnPlsDunBreak != nullptr) _btnPlsDunBreak->draw();
}	