#include "../stdafx.h"		
#include "Kingdom.h"
#include "WorldMap.h"

// #define S2D (Sandbox2D::GetSingleton())

Kingdom::Kingdom(
	const std::string name,
	const RGBA color,
	WorldMap *worldMap
) :
	_name(name),
	_color(color),
	_worldMap(worldMap)
{
}

Kingdom::~Kingdom()
{
}

void Kingdom::tick(double deltaTime)
{
}

void Kingdom::draw(Graphics* g)
{
}

void Kingdom::selectTile(const Pixel position)
{
	if (Contains(Rect<int>{ Pixel{ 0, 0 }, _worldMap->getSize() }, position))
	{
		_currentlySelectedTile = _worldMap->findTileAtPosition(position);
		_currentlySelectedTile->setOwner(this);
	}

}

RGBA Kingdom::getColor()
{
	return _color;
}

Resources Kingdom::getResources()
{
	return _resources;
}

WorldTile* Kingdom::getCurrentlySelectedTile()
{
	return _currentlySelectedTile;
}
