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

	_btnPlsDunBreak = new ButtonWidget({ 10, 100 });
	_btnPlsDunBreak->_text = "Click me to potentially break shit";
	_btnPlsDunBreak->_textPadding = { 10,100,10,100 };
	On(_btnPlsDunBreak->_ob, "clicked", [](Event e)
	{
		Log("Did it break?");
	});

	_testOb = new Observer();
	On(_testOb, "test", [](Event e)
	{
		Log("Event \"test\" was fired!");
	});
	
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
	if (_btnTestState->isPressed())
	{
		delete _testOb;
		_testOb = nullptr;

		delete _btnPlsDunBreak;
		_btnPlsDunBreak = nullptr;
	}
	if (_testOb == nullptr)
	{
		_btnTestState->_text = "Observer was deleted";
		_btnTestState->resizeToText();
		_btnTestState->_backColor = { 255, 0, 0, 255 };
	}
	if (S2D->_inputManager->IsKeyboardKeyPressed(SDL_SCANCODE_E))
	{
		std::cout << _testOb << std::endl;

		Emit(_testOb, Event{ "test", Any::Any(0) }, [](Any::Any any)
		{
			any.free<int>();
		});
		
	}
}

void EntryState::statePaint(Graphics* g)
{
	// Executed after game tick, game drawing calls go 
	_lblInfo->draw();
	_btnTestState->draw();
	if (_btnPlsDunBreak != nullptr) _btnPlsDunBreak->draw();
}	