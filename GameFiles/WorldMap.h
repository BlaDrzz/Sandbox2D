#pragma once
#include "WorldTile.h"

#define TILE_SIZE 32

class WorldMap
{
public:
	WorldMap(Pixel size);
	virtual ~WorldMap();
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	WorldMap( const WorldMap& ) = delete;
	WorldMap& operator=( const WorldMap& ) = delete;

	void tick(double deltaTime);
	void draw(Graphics* g);

	void addTile(WorldTile* tile);
	WorldTile* findTileAtPosition(Pixel position);

	Pixel getSize();
private: 
	std::vector<WorldTile*> _tiles;
	Pixel _size = { 0, 0 };
};
