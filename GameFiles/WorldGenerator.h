#pragma once

class WorldMap;
class WorldTile;

class WorldGenerator
{
public:
	WorldGenerator() = default;
	virtual ~WorldGenerator() = default;
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	WorldGenerator(const WorldGenerator&) = delete;
	WorldGenerator& operator=(const WorldGenerator&) = delete;

	WorldMap* generateWorldMap(int size);
private:
	WorldTile* pickTileBasedOnValue(int value, Pixel position);
};
