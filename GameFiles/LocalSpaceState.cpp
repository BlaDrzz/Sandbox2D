#include "../stdafx.h"
#include "LocalSpaceState.h"
#include "PlayerController.h"

#define S2D (Sandbox2D::GetSingleton())

LocalSpaceState::LocalSpaceState() {}
LocalSpaceState::~LocalSpaceState() {}

void LocalSpaceState::stateStart()
{
	S2D->setGravity({ 0, 0 });
	_player = new PlayerController();
}

void LocalSpaceState::stateEnd()
{
	delete _player;
}

void LocalSpaceState::stateTick(double deltaTime) 
{
	_player->tick(deltaTime);
}

void LocalSpaceState::statePaint(Graphics* g)
{
	g->backgroundDrawingColor = MakeRGBA(0, 0, 0);
	_player->draw(g);
}