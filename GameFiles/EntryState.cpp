#pragma once

// +----------------------------------------------------------------------------------------------------+
// | THIS STATE IS THE ONLY STATE WHICH CAN NOT BE DELETED! THE ENGINE USES THIS STAGE AS ENTRY POINT!! |
// +----------------------------------------------------------------------------------------------------+

// Include files
#include "../stdafx.h"
#include "EntryState.h"
#include "PhysicsTestState.h"
#include "AudioTestState.h"

// Defines
#define S2D (Sandbox2D::GetSingleton())

// EntryState methods
EntryState::EntryState() {}
EntryState::~EntryState() {}

void EntryState::stateStart()
{
	// Executed at start of state
	_btnSwitchToPhysics = new ButtonWidget({ 10,10 }, "Switch To Physics");
	_btnSwitchToAudio = new ButtonWidget({ 10,50 }, "Switch To Audio");
}

void EntryState::stateEnd()
{
	// Executed at end of state

	delete _btnSwitchToPhysics;
	delete _btnSwitchToAudio;
}

void EntryState::stateTick(double deltaTime) 
{
	// Executed each game tick, game logic goes here
	if (_btnSwitchToPhysics->isPressed()) S2D->pushState(new PhysicsTestState());

	if (_btnSwitchToAudio->isPressed())	S2D->pushState(new AudioTestState());
}

void EntryState::statePaint(Graphics* g)
{
	// Executed after game tick, game drawing calls go 
	_btnSwitchToPhysics->draw(g);
	_btnSwitchToAudio->draw(g);
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void EntryState::beginContact(PhysicsObject* actThisPtr, PhysicsObject* actOtherPtr)
{
}

void EntryState::endContact(PhysicsObject* actThisPtr, PhysicsObject* actOtherPtr)
{
}

void EntryState::contactImpulse(PhysicsObject* actThisPtr, double impulse)
{
}	