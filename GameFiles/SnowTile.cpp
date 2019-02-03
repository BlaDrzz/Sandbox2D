#include "../stdafx.h"

#include "WorldTile.h"
#include "SnowTile.h"
#include "WorldMap.h"
#include "Kingdom.h"

#define S2D (Sandbox2D::GetSingleton())

SnowTile::SnowTile(const Pixel position) : WorldTile(position), _color(Colors::white())
{
}

SnowTile::~SnowTile()
{
}

void SnowTile::tick(const double deltaTime)
{
}

void SnowTile::draw(Graphics* g)
{
	g->setColor(_color);
	const auto tileRect = Rect<int>{
		_position,
		{ _position.x + TILE_SIZE, _position.y + TILE_SIZE }
	};
	g->drawRect(true, tileRect);
}
