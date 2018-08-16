#pragma once

class Ship;

class PlayerController //: public ContactListener
{
public:
	PlayerController( );
	virtual ~PlayerController( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	PlayerController( const PlayerController& ) = delete;
	PlayerController& operator=( const PlayerController& ) = delete;

	void tick(double deltaTime);
	void draw(Graphics* g);

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	// virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	// virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	// virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);

private:
	void drawHud(Graphics* g);
	LabelWidget* _shipPosLabel = nullptr;

	Ship* _playerShip = nullptr;

	PanelWidget* fullPanel = nullptr;
	PanelWidget* downLeftPanel = nullptr;
	PanelWidget* energyWidget = nullptr;
	PanelWidget* oxygenWidget = nullptr;
	PanelWidget* fuelWidget = nullptr;
	BitmapWidget* circleWithBar1 = nullptr;
	BitmapWidget* circleWithBar2 = nullptr;
	BitmapWidget* circleWithBar3 = nullptr;

	void createHUD();
};
