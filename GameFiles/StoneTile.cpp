#include "../stdafx.h"

#include "WorldTile.h"
#include "StoneTile.h"
#include "WorldMap.h"
#include "Kingdom.h"

#define S2D (Sandbox2D::GetSingleton())

StoneTile::StoneTile(const Pixel position) : WorldTile(position), _color(Colors::gray())
{
}

StoneTile::~StoneTile()
{
}

void StoneTile::tick(const double deltaTime)
{
}

void StoneTile::draw(Graphics* g)
{
	g->setColor(_color);
	const auto tileRect = Rect<int>{
		_position,
		{ _position.x + TILE_SIZE, _position.y + TILE_SIZE }
	};
	g->drawRect(true, tileRect);
}
