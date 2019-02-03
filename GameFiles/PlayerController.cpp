#include "../stdafx.h"		
#include "Kingdom.h"
#include "PlayerController.h"

// #define S2D (Sandbox2D::GetSingleton())

PlayerController::PlayerController(Kingdom* kingdom) : _kingdom(kingdom)
{
}

PlayerController::~PlayerController()
{
	delete _kingdom;
}

void PlayerController::tick(double deltaTime)
{
	if (S2D->inputManager->isMouseButtonReleased(SDL_BUTTON_LEFT))
	{
		_kingdom->selectTile(S2D->inputManager->getMousePos());
	}
}

void PlayerController::draw(Graphics* g)
{
}
