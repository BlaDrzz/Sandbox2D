#pragma once

class SandTile : public WorldTile
{
public:
	SandTile(Pixel position);
	virtual ~SandTile();
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	SandTile(const SandTile&) = delete;
	SandTile& operator=(const SandTile&) = delete;

	void tick(double deltaTime) override;
	void draw(Graphics* g) override;
	void setOwner(Kingdom* kingdom) override {};

private:
	RGBA _color;
};
