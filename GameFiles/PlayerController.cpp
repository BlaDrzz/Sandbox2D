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
	delete _fullPanel;
	delete _mapBmp;
	delete _mapShipBmp;
	delete _circleWithBarBmp;
	for (int i = 0; i < _circleBmpVector.size(); i++) 
	{
		delete _circleBmpVector[i];
	}
	_circleBmpVector.empty();
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
	g->setColor(MakeRGBA(255, 255, 255));
	_shipPosLabel->_text = "Ship's location: " + std::to_string(_playerShip->getShipPosition().x) + ", " + std::to_string(_playerShip->getShipPosition().y);
	_shipPosLabel->draw(g);

	// draw every widget in bottomLeftPanel (for now)
	_circleWithBar1->draw(g);
	_circleWithBar2->draw(g);
	_circleWithBar3->draw(g);
	_energyPercentage->draw(g);
	_energyTextLeft->draw(g);
	_energyTextRight->draw(g);
	_oxygenPercentage->draw(g);
	_oxygenTextLeft->draw(g);
	_oxygenTextRight->draw(g);
	_fuelPercentage->draw(g);	
	_fuelTextLeft->draw(g);	
	_fuelTextRight->draw(g);

	// draw every widget in topLeftPanel (for now)
	_map->draw(g);
	_mapShip->draw(g);

	// draw every widget in bottomLeftPanel (for now)
	for (int i = 0; i < _circleVector.size(); i++) 
	{
		_circleVector[i]->draw(g);
		_weaponLabelVector[i]->draw(g);
		_weaponAmmoVector[i]->draw(g);
	}
}

void PlayerController::createHUD()
{
	// For now the values are set. Later they will be called by _playerShip->getEnergy()...
	double shipEnergyInAH = 1485;
	double shipOxygenInLiters = 60000;
	double shipFuelInTons = 2000;
	double shipMaxEnergy = 2000;
	double shipMaxOxygen = 65000;
	double shipMaxFuel = 4000;
	double shipEnergyInPercentage = (shipEnergyInAH / shipMaxEnergy) * 100;
	double shipOxygenInPercentage = (shipOxygenInLiters / shipMaxOxygen) * 100;
	double shipFuelInPercentage = (shipFuelInTons / shipMaxFuel) * 100;
	std::string energyTextLeftString = "ENERGY";
	std::string oxygenTextLeftString = "OXYGEN";
	std::string fuelTextLeftString = "FUEL";
	std::string energyTextRightString = std::to_string((int)shipEnergyInAH) + " / " + std::to_string((int)shipMaxEnergy) + " AH";
	std::string oxygenTextRightString = std::to_string((int)shipOxygenInLiters) + " / " + std::to_string((int)shipMaxOxygen) + " Liters";;
	std::string fuelTextRightString = std::to_string((int)shipFuelInTons) + " / " + std::to_string((int)shipMaxFuel) + " Tons";;

	_fullPanel = new PanelWidget({ 0,0 });

	// create bottomLeftPanel widgets
	_bottomLeftPanel = new PanelWidget({ 40,S2D->getWindowSize().y - 56 });
	_energyWidget = new PanelWidget({ 0,-150 });
	_oxygenWidget = new PanelWidget({ 0,-100 });
	_fuelWidget = new PanelWidget({ 0,-50 });
	_circleWithBarBmp = new Bitmap("Resources/HUD_circle_with_bar.png");
	_circleWithBar1 = new BitmapWidget(_circleWithBarBmp, { 0,0 });
	_circleWithBar2 = new BitmapWidget(_circleWithBarBmp, { 0,0 });
	_circleWithBar3 = new BitmapWidget(_circleWithBarBmp, { 0,0 });
	_energyPercentage = new LabelWidget(std::to_string((int)shipEnergyInPercentage), { 28,28 });
	_oxygenPercentage = new LabelWidget(std::to_string((int)shipOxygenInPercentage), { 28,28 });
	_fuelPercentage = new LabelWidget(std::to_string((int)shipFuelInPercentage), { 28,28 });
	_energyTextLeft = new LabelWidget(energyTextLeftString, { 65,10 });
	_oxygenTextLeft = new LabelWidget(oxygenTextLeftString, { 65,10 });
	_fuelTextLeft = new LabelWidget(fuelTextLeftString, { 65,10 });
	_energyTextRight = new LabelWidget(energyTextRightString, { 300,10 });
	_oxygenTextRight = new LabelWidget(oxygenTextRightString, { 300,10 });
	_fuelTextRight = new LabelWidget(fuelTextRightString, { 300,10 });

	// create topLeftPanel widgets
	_topLeftPanel = new PanelWidget({ 40,40 });
	_mapBmp = new Bitmap("Resources/HUD_map.png");
	_map = new BitmapWidget(_mapBmp, { 0,0 });
	_mapShipBmp = new Bitmap("Resources/HUD_map_ship.png");
	_mapShip = new BitmapWidget(_mapShipBmp, { _mapBmp->getSize().x/2-_mapShipBmp->getSize().x/2,_mapBmp->getSize().y/2-_mapShipBmp->getSize().y/2 });

	// create bottomRightPanel widgets
	_bottomRightPanel = new PanelWidget({ S2D->getWindowSize().x - 56,S2D->getWindowSize().y - 56 });
	std::vector<std::string> weapons = { "SMALL", "MEDIUM", "LARGE", "MISSILES" }; // weapons will depend on weapons of _playerShip
	std::vector<std::string> weaponsAmmo = { "80", "54", "20", "5" }; // weapons ammo will depend on weapons ammo of _playerShip
	for (int i = 0; i < weapons.size(); i++) 
	{
		PanelWidget* weapon = new PanelWidget({ -50,-50*(i+1) });
		Bitmap* circleBmp = new Bitmap("Resources/HUD_circle.png");
		BitmapWidget* circle = new BitmapWidget(circleBmp, { 0,0 });
		LabelWidget* weaponText = new LabelWidget(weapons[i], { -56,28 });
		LabelWidget* weaponAmmo = new LabelWidget(weaponsAmmo[i], { 28,28 });

		weapon->add(circle);
		weapon->add(weaponText);
		weapon->add(weaponAmmo);

		_circleBmpVector.push_back(circleBmp);
		_circleVector.push_back(circle);
		_weaponLabelVector.push_back(weaponText);
		_weaponAmmoVector.push_back(weaponAmmo);
		_weaponVector.push_back(weapon);
	}

	// build _topLeftPanel
	_topLeftPanel->add(_map);
	_topLeftPanel->add(_mapShip);

	// build _bottomLeftPanel
	_energyWidget->add(_circleWithBar1);
	_energyWidget->add(_energyTextLeft);
	_energyWidget->add(_energyTextRight);
	_energyWidget->add(_energyPercentage);
	_oxygenWidget->add(_circleWithBar2);
	_oxygenWidget->add(_oxygenTextLeft);
	_oxygenWidget->add(_oxygenTextRight);
	_oxygenWidget->add(_oxygenPercentage);
	_fuelWidget->add(_circleWithBar3);
	_fuelWidget->add(_fuelTextLeft);
	_fuelWidget->add(_fuelTextRight);
	_fuelWidget->add(_fuelPercentage);
	_bottomLeftPanel->add(_energyWidget);
	_bottomLeftPanel->add(_oxygenWidget);
	_bottomLeftPanel->add(_fuelWidget);

	// build _bottomRightPanel
	for (int i = 0; i < _weaponVector.size(); i++) 
	{
		_bottomRightPanel->add(_weaponVector[i]);
	}

	// build _fullPanel
	_fullPanel->add(_topLeftPanel);
	_fullPanel->add(_bottomLeftPanel);
	_fullPanel->add(_bottomRightPanel);
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