#include "../stdafx.h"

#include "WorldTile.h"
#include "WaterTile.h"
#include "WorldMap.h"
#include "Kingdom.h"

#define S2D (Sandbox2D::GetSingleton())

WaterTile::WaterTile(const Pixel position) : WorldTile(position), _color(Colors::blue())
{
}

WaterTile::~WaterTile()
{
}

void WaterTile::tick(const double deltaTime)
{
}

void WaterTile::draw(Graphics* g)
{
	g->setColor(_color);
	const auto tileRect = Rect<int>{
		_position,
		{ _position.x + TILE_SIZE, _position.y + TILE_SIZE }
	};
	g->drawRect(true, tileRect);
}
