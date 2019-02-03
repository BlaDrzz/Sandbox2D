#pragma once

class GrassTile : public WorldTile
{
public:
	GrassTile(Pixel position);
	virtual ~GrassTile();
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	GrassTile(const GrassTile&) = delete;
	GrassTile& operator=(const GrassTile&) = delete;

	void tick(double deltaTime) override;
	void draw(Graphics* g) override;

private:
	RGBA _color = MakeRGBA(0, 220, 25);
};
