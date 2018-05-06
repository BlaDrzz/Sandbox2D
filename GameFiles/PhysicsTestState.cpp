#pragma once

// Include files
#include "../stdafx.h"
#include "PhysicsTestState.h"

// Defines
#define S2D (Sandbox2D::GetSingleton())

// PhysicsTestState methods
PhysicsTestState::PhysicsTestState() {}
PhysicsTestState::~PhysicsTestState() {}

void PhysicsTestState::stateStart()
{
	// Executed at start of state
	_lblInfo = new LabelWidget("S2D Physics test. WASD to move, ESC to return.", { 10,10 });

	S2D->setGravity({ 0,0 });

	_poTestObj = new PhysicsObject(ToVector2(S2D->getWindowSize()) / double(2), 0, BodyType::DYNAMIC);
	_poTestObj->addBoxFixture({ 400, 400 });
	_poTestObj->addContactListener(this);
	_poTestObj->getBody()->SetLinearDamping(2.0f);
	_poTestObj->setAngularVelocity(10);

	_poTestObj2 = new PhysicsObject({ 1000,100 }, 0, BodyType::DYNAMIC);
	_poTestObj2->addBoxFixture({ 200, 200 });
	_poTestObj2->addContactListener(this);
	_poTestObj2->setFixedRotation(true);

	_bmpTest = new Bitmap("Resources/blue.png");
}

void PhysicsTestState::stateEnd()
{
	// Executed at end of state
	delete _lblInfo;
	delete _poTestObj;
	delete _poTestObj2;
	delete _bmpTest;
}

void PhysicsTestState::stateTick(double deltaTime) 
{
	// Executed each game tick, game logic goes here
	_poTestObj->setLinearVelocity(Vector2{ 0,0 });

	if (S2D->_inputManager->isKeyboardKeyDown(SDL_SCANCODE_A))
	{
		_poTestObj->applyLinearImpulse({ -1000,0 });	
	}
	if (S2D->_inputManager->isKeyboardKeyDown(SDL_SCANCODE_W))
	{
		_poTestObj->applyLinearImpulse({ 0,-1000 });
	}
	if (S2D->_inputManager->isKeyboardKeyDown(SDL_SCANCODE_S))
	{
		_poTestObj->applyLinearImpulse({ 0,1000 });
	}
	if (S2D->_inputManager->isKeyboardKeyDown(SDL_SCANCODE_D))
	{
		_poTestObj->applyLinearImpulse({ 1000,0 });
	}

	if (S2D->_inputManager->isKeyboardKeyPressed(SDL_SCANCODE_ESCAPE)) S2D->popState();
}

void PhysicsTestState::statePaint(Graphics* g)
{
	// Executed after game tick, game drawing calls go 
	g->_backgroundDrawingColor = MakeRGBA(200, 200, 200);

	g->_viewPort._position = Pixel{
		int(_poTestObj->getPosition().x) - S2D->getWindowSize().x / 2,
		int(_poTestObj->getPosition().y) - S2D->getWindowSize().y / 2
	};

	g->drawBitmap(_bmpTest, ToPixel(_poTestObj->getPosition() - Vector2{ 200,200 }), _poTestObj->getAngleDeg());

	g->drawRect(true, Rect<int>{
		int(_poTestObj2->getPosition().x) - 100,
		int(_poTestObj2->getPosition().y) - 100,
		int(_poTestObj2->getPosition().x) + 100,
		int(_poTestObj2->getPosition().y) + 100,
	});

	g->_viewPort.defaults();
	_lblInfo->draw(g);
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void PhysicsTestState::beginContact(PhysicsObject* actThisPtr, PhysicsObject* actOtherPtr)
{
	Log("THEY COLLIDED!!!???");
}

void PhysicsTestState::endContact(PhysicsObject* actThisPtr, PhysicsObject* actOtherPtr)
{
}

void PhysicsTestState::contactImpulse(PhysicsObject* actThisPtr, double impulse)
{
}	