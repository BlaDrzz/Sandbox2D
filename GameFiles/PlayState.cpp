// Include files
#include "../stdafx.h"
#include "WorldGenerator.h"
#include "PlayerController.h"
#include "WorldMap.h"
#include "PlayState.h"
#include "Kingdom.h"

// Defines
#define S2D (Sandbox2D::GetSingleton())

void PlayState::stateStart()
{
	_btnBack = new ButtonWidget(Pixel{ S2D->getWindowSize().x - 10, 10 }, "Back");
	_btnBack->alignment = BUTTON_ALIGN::TOPRIGHT;

	WorldGenerator worldGen;
	_worldMap = worldGen.generateWorldMap(32);

	const auto playerKingdom = new Kingdom("Player kingdom", Colors::blue(), _worldMap);
	_playerController = new PlayerController(playerKingdom);
}

void PlayState::stateEnd()
{
	delete _btnBack;
	delete _worldMap;
	delete _playerController;
}

void PlayState::stateTick(const double deltaTime)
{
	if (_btnBack->isPressed())
	{
		S2D->popState();
		return;
	}
	_worldMap->tick(deltaTime);
	_playerController->tick(deltaTime);
}

void PlayState::statePaint(Graphics* g)
{
	_btnBack->draw(g);
	_worldMap->draw(g);
}