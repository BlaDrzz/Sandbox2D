#include "../stdafx.h"		
#include "WorldMap.h"

#define S2D (Sandbox2D::GetSingleton())

WorldMap::WorldMap(const Pixel size) : _size(size)
{
}

WorldMap::~WorldMap()
{
	for (auto tile : _tiles)
	{
		delete tile;
	}
}

void WorldMap::tick(const double deltaTime)
{
	for (auto tile : _tiles)
	{
		tile->tick(deltaTime);
	}
}

void WorldMap::draw(Graphics* g)
{
	g->backgroundDrawingColor = Colors::black();
	for (auto tile : _tiles)
	{
		tile->draw(g);
	}
}

void WorldMap::addTile(WorldTile* tile)
{
	_tiles.push_back(tile);
}

WorldTile* WorldMap::findTileAtPosition(const Pixel position)
{
	const auto normalisedX = position.x / TILE_SIZE;
	const auto normalisedY = position.y / TILE_SIZE * TILE_SIZE;

	const auto posInVec = normalisedX + normalisedY;
	return _tiles[posInVec];
}

Pixel WorldMap::getSize()
{
	return _size;
}
