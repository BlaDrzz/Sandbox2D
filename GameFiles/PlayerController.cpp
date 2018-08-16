#include "../stdafx.h"		
#include "PlayerController.h"
#include "Ship.h"

// #define S2D (Sandbox2D::GetSingleton())

PlayerController::PlayerController()
{
	_playerShip = new Ship({ 0, 0 });
	_shipPosLabel = new LabelWidget("Ship's location: ", { 10, 10 });

	createHUD();

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
	_shipPosLabel->_text = "Ship's location: " + std::to_string(_playerShip->getShipPosition().x) + ", " + std::to_string(_playerShip->getShipPosition().y);
	_shipPosLabel->draw(g);

	circleWithBar1->draw(g);
	circleWithBar2->draw(g);
	circleWithBar3->draw(g);
	//downLeftPanel->draw(g);
	//fullPanel->draw(g);

}

void PlayerController::createHUD()
{
	Pixel windowSize = S2D->getWindowSize();
	int windowWidth = windowSize.x;
	int windowHeight = windowSize.y;
	Log(std::to_string(windowHeight));

	fullPanel = new PanelWidget({ 0,0 });
	downLeftPanel = new PanelWidget({ 40,windowHeight-40 });
	energyWidget = new PanelWidget({ 0,-50 });
	oxygenWidget = new PanelWidget({ 0,-100 });
	fuelWidget = new PanelWidget({ 0,-150 });
	Bitmap* circleWithBarBmp = new Bitmap("Resources/HUD_circle_with_bar.png");
	circleWithBar1 = new BitmapWidget(circleWithBarBmp, { 0,0 });
	circleWithBar2 = new BitmapWidget(circleWithBarBmp, { 0,0 });
	circleWithBar3 = new BitmapWidget(circleWithBarBmp, { 0,0 });

	energyWidget->add(circleWithBar1);
	oxygenWidget->add(circleWithBar2);
	fuelWidget->add(circleWithBar3);
	downLeftPanel->add(energyWidget);
	downLeftPanel->add(oxygenWidget);
	downLeftPanel->add(fuelWidget);
	fullPanel->add(downLeftPanel);
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