#pragma once

// Include files
#include "../stdafx.h"
#include "EXAMPLESTATE.h"

// Defines
#define S2D (Sandbox2D::GetSingleton())

// EXAMPLESTATE methods
EXAMPLESTATE::EXAMPLESTATE() {}
EXAMPLESTATE::~EXAMPLESTATE() {}

void EXAMPLESTATE::stateStart()
{
	// Executed at start of state
}

void EXAMPLESTATE::stateEnd()
{
	// Executed at end of state
}

void EXAMPLESTATE::stateTick(double deltaTime) 
{
	// Executed each game tick, game logic goes here


}

void EXAMPLESTATE::statePaint(Graphics* g)
{
	// Executed after game tick, game drawing calls go 
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void EXAMPLESTATE::beginContact(PhysicsObject* actThisPtr, PhysicsObject* actOtherPtr)
{
}

void EXAMPLESTATE::endContact(PhysicsObject* actThisPtr, PhysicsObject* actOtherPtr)
{
}

void EXAMPLESTATE::contactImpulse(PhysicsObject* actThisPtr, double impulse)
{
}	