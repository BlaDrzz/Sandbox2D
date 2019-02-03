#pragma once

class StoneTile : public WorldTile
{
public:
	StoneTile(Pixel position);
	virtual ~StoneTile();
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	StoneTile(const StoneTile&) = delete;
	StoneTile& operator=(const StoneTile&) = delete;

	void tick(double deltaTime) override;
	void draw(Graphics* g) override;
	void setOwner(Kingdom* kingdom) override {};

private:
	RGBA _color;
};
