#pragma once

// Include files
#include "stdafx.h"
#include "EntryState.h"

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

	_poTestObj = new PhysicsObject({ 200,200 }, 0, BodyType::DYNAMIC);
	_poTestObj->addBoxFixture({ 100, 100 });
	_poTestObj->addContactListener(this);
	_poTestObj->getBody()->SetAwake(false);

	_poTestObj2 = new PhysicsObject({ 1000, 250 }, 0, BodyType::DYNAMIC);
	_poTestObj2->addBoxFixture({ 100, 100 });
	_poTestObj2->addContactListener(this);
	_poTestObj2->getBody()->SetAwake(false);
}

void EntryState::stateEnd()
{
	// Executed at end of state
	delete _btnTestState;
	delete _lblInfo;
	delete _poTestObj;
	delete _poTestObj2;
}

void EntryState::stateTick(double deltaTime) 
{
	// Executed each game tick, game logic goes here
	if (S2D->_inputManager->isKeyboardKeyPressed(SDL_SCANCODE_A))
	{
		_poTestObj->setLinearVelocity({ 2000,10 });
		_poTestObj2->setLinearVelocity({ -2000,10 });
	}
}

void EntryState::statePaint(Graphics* g)
{
	// Executed after game tick, game drawing calls go 
	_lblInfo->draw();
	_btnTestState->draw();
	if (_btnPlsDunBreak != nullptr) _btnPlsDunBreak->draw();

	const auto poPos = _poTestObj->getPosition();

	const Rect<int> poRect = {
		{ poPos.x - 50, poPos.y - 50 },
		{ poPos.x + 50, poPos.y + 50 }
	};
	g->setColor({ 0,0,255,255 });
	g->drawRect(true, poRect);

	const auto poPos2 = _poTestObj2->getPosition();

	const Rect<int> poRect2 = {
		{ poPos2.x - 50, poPos2.y - 50 },
		{ poPos2.x + 50, poPos2.y + 50 }
	};
	g->setColor({ 255,0,255,255 });
	g->drawRect(true, poRect2);
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void EntryState::beginContact(PhysicsObject* actThisPtr, PhysicsObject* actOtherPtr)
{
	Log("THEY COLLIDED!!!???");
}

void EntryState::endContact(PhysicsObject* actThisPtr, PhysicsObject* actOtherPtr)
{
}

void EntryState::contactImpulse(PhysicsObject* actThisPtr, double impulse)
{
}	