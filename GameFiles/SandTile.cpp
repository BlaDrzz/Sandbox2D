#include "../stdafx.h"

#include "WorldTile.h"
#include "SandTile.h"
#include "WorldMap.h"
#include "Kingdom.h"

#define S2D (Sandbox2D::GetSingleton())

SandTile::SandTile(const Pixel position) : WorldTile(position), _color(Colors::yellow())
{
}

SandTile::~SandTile()
{
}

void SandTile::tick(const double deltaTime)
{
}

void SandTile::draw(Graphics* g)
{
	g->setColor(_color);
	const auto tileRect = Rect<int>{
		_position,
		{ _position.x + TILE_SIZE, _position.y + TILE_SIZE }
	};
	g->drawRect(true, tileRect);
}
