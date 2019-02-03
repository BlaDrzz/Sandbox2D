#pragma once

class WorldMap;
class WorldTile;

struct Resources
{
	int gold = 100;
};

class Kingdom
{
public:
	Kingdom(std::string name, RGBA color, WorldMap *worldMap);
	virtual ~Kingdom();
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	Kingdom(const Kingdom&) = delete;
	Kingdom& operator=(const Kingdom&) = delete;

	void tick(double deltaTime);
	void draw(Graphics* g);
	void selectTile(Pixel position);

	RGBA getColor();
	Resources getResources();
	WorldTile* getCurrentlySelectedTile();
private:
	std::string _name;
	RGBA _color;
	Resources _resources;
	WorldMap* _worldMap;
	WorldTile* _currentlySelectedTile = nullptr;
};
