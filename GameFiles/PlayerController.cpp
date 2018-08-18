#include "../stdafx.h"		
#include "PlayerController.h"
#include "Ship.h"

// #define S2D (Sandbox2D::GetSingleton())

PlayerController::PlayerController()
{
	_playerShip = new Ship({ 0, 0 });
	_shipPosLabel = new LabelWidget("Ship's location: ", { 10, 10 });
}

PlayerController::~PlayerController()
{
	delete _playerShip;
	delete _shipPosLabel;
}

void PlayerController::tick(double deltaTime)
{
	const auto deltaPoint = ToVector2(S2D->inputManager->getMousePos()) - ToVector2(S2D->getWindowSize() / 2);

	_playerShip->targetAngle = atan2(deltaPoint.y, deltaPoint.x);

	_playerShip->tick(deltaTime);
	if (S2D->inputManager->isKeyboardKeyDown(SDL_SCANCODE_LSHIFT))
	{
		_playerShip->accelerate(deltaTime);
	}
}

void PlayerController::draw(Graphics* g)
{
	drawHud(g);
	g->viewPort.position = ToPixel(_playerShip->getShipPosition()) - S2D->getWindowSize() / 2;
	_playerShip->draw(g);
}

void PlayerController::drawHud(Graphics* g)
{
	g->viewPort.position = { 0, 0 };
	g->setColor(MakeRGBA(255, 0, 0));
	_shipPosLabel->text = "Ship's location: " + std::to_string(_playerShip->getShipPosition().x) + ", " + std::to_string(_playerShip->getShipPosition().y);
	_shipPosLabel->draw(g);
}

//-------------------------------------------------------
// ContactListener overloaded member funRction definitions
//-------------------------------------------------------
// void PlayerController::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
// {
// }
// 
// void PlayerController::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
// {
// }
// 
// void PlayerController::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
// {
// }