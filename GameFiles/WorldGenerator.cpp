#include "../stdafx.h"		
#include "WorldMap.h"
#include "WaterTile.h"
#include "GrassTile.h"
#include "WorldGenerator.h"
#include "PerlinNoise.h"
#include "SnowTile.h"
#include "SandTile.h"
#include "StoneTile.h"

// #define S2D (Sandbox2D::GetSingleton())

WorldMap* WorldGenerator::generateWorldMap(const int size)
{
	const auto maxSize = Pixel{ TILE_SIZE * size, TILE_SIZE * size };
	auto worldMap = new WorldMap(maxSize);

	PerlinNoise perlin;
	const auto perlinMap = perlin.generatePerlinNoise(size * rand(), size * 5, size * 5, 1000);

	auto currentPos = Pixel{ 0, 0 };
	for (auto y = 0; y < size; y++)
	{
		for (auto x = 0; x < size; x++)
		{
			const auto tileValue = perlinMap[y][x];
			worldMap->addTile(pickTileBasedOnValue(tileValue, currentPos));

			currentPos.x += TILE_SIZE;
		}
		currentPos.x = 0;
		currentPos.y += TILE_SIZE;
	}

	return worldMap;
}

WorldTile* WorldGenerator::pickTileBasedOnValue(const int value, const Pixel position)
{
	WorldTile* tile;

	if (value < 300) tile = new WaterTile(position);
	else if (value < 375) tile = new SandTile(position);
	else if (value < 700) tile = new GrassTile(position);
	else if (value < 850) tile = new StoneTile(position);
	else tile = new SnowTile(position);

	return tile;
}
