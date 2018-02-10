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
	_lblInfo = new LabelWidget("S2D Physics test.", { 10,10 });

	S2D->setGravity({ 0,0 });

	_poTestObj = new PhysicsObject({ 200,200 }, 0, BodyType::DYNAMIC);
	_poTestObj->addBoxFixture({ 100, 100 });
	_poTestObj->addContactListener(this);
	_poTestObj->getBody()->SetLinearDamping(2.0f);
}

void EntryState::stateEnd()
{
	// Executed at end of state
	delete _lblInfo;
	delete _poTestObj;
}

void EntryState::stateTick(double deltaTime) 
{
	// Executed each game tick, game logic goes here
	if (S2D->_inputManager->isKeyboardKeyDown(SDL_SCANCODE_A))
	{
		_poTestObj->applyForce({ 500,0 });	
	}
}

void EntryState::statePaint(Graphics* g)
{
	// Executed after game tick, game drawing calls go 
	_lblInfo->draw();

	const auto poPos = ToPixel(_poTestObj->getPosition());

	const Rect<int> poRect = {
		{ poPos.x - 50, poPos.y - 50 },
		{ poPos.x + 50, poPos.y + 50 }
	};
	g->setColor({ 0,0,255,255 });
	g->drawRect(true, poRect);
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