#pragma once

class Kingdom;

class PlayerController
{
public:
	PlayerController(Kingdom* kingdom);
	virtual ~PlayerController();
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	PlayerController( const PlayerController& ) = delete;
	PlayerController& operator=( const PlayerController& ) = delete;

	void tick(double deltaTime);
	void draw(Graphics* g);
private: 
	Kingdom* _kingdom;
};
