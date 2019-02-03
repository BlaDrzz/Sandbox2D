#include "../stdafx.h"		
#include "WorldMap.h"
#include "GrassTile.h"
#include "WorldGenerator.h"

// #define S2D (Sandbox2D::GetSingleton())

WorldMap* WorldGenerator::generateWorldMap(const int size)
{
	const auto maxSize = Pixel{ TILE_SIZE * size, TILE_SIZE * size };
	auto worldMap = new WorldMap(maxSize);

	auto currentPos = Pixel{ 0, 0 };
	for (auto i = 0; i < size; ++i)
	{
		for (auto j = 0; j < size; ++j)
		{
			const auto tile = new GrassTile(currentPos);
			worldMap->addTile(tile);

			currentPos.x += TILE_SIZE;
		}
		currentPos.x = 0;
		currentPos.y += TILE_SIZE;
	}

	return worldMap;
}