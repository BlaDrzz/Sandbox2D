#pragma once

class SnowTile : public WorldTile
{
public:
	SnowTile(Pixel position);
	virtual ~SnowTile();
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	SnowTile(const SnowTile&) = delete;
	SnowTile& operator=(const SnowTile&) = delete;

	void tick(double deltaTime) override;
	void draw(Graphics* g) override;
	void setOwner(Kingdom* kingdom) override {};

private:
	RGBA _color;
};
