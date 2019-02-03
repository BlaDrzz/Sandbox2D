#pragma once

class Kingdom;

class WorldTile
{
public:
	WorldTile(const Pixel position) : _position(position) {};
	virtual ~WorldTile() = default;
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	WorldTile(const WorldTile&) = delete;
	WorldTile& operator=(const WorldTile&) = delete;

	virtual void tick(double deltaTime) = 0;
	virtual void draw(Graphics* g) = 0;

	void setOwner(Kingdom* newOwner)
	{
		_owner = newOwner;
	}

protected:
	Pixel _position;
	Kingdom* _owner = nullptr;
};
