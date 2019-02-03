// +-----------------------------------------------------------------------------------------------+
// | THE ENGINE USES THIS STATE AS ENTRY POINT!! DO NOT REMOVE UNLESS YOU KNOW WHAT YOU'RE DOING!! |
// +-----------------------------------------------------------------------------------------------+

// Include files
#include "../stdafx.h"
#include "EntryState.h"
#include "PlayState.h"

// Defines
#define S2D (Sandbox2D::GetSingleton())

// EntryState methods
EntryState::EntryState() {}
EntryState::~EntryState() {}

void EntryState::stateStart()
{
	_btnStart = new ButtonWidget(Pixel{ 10, 10 }, "Start new game");
}

void EntryState::stateEnd()
{
	delete _btnStart;
}

void EntryState::stateTick(double deltaTime)
{
	if (_btnStart->isPressed())
	{
		S2D->pushState(new PlayState());
	}
}

void EntryState::statePaint(Graphics* g)
{
	_btnStart->draw(g);
}