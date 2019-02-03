#pragma once

class WaterTile : public WorldTile
{
public:
	WaterTile(Pixel position);
	virtual ~WaterTile();
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	WaterTile(const WaterTile&) = delete;
	WaterTile& operator=(const WaterTile&) = delete;

	void tick(double deltaTime) override;
	void draw(Graphics* g) override;
	void setOwner(Kingdom* kingdom) override {};

private:
	RGBA _color;
};
