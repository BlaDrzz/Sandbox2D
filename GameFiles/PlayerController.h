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
	LabelWidget* _shipPosLabel = nullptr;
	Ship* _playerShip = nullptr;

	PanelWidget* _fullPanel = nullptr;

	// bottomLeftPanel
	PanelWidget* _bottomLeftPanel = nullptr;
	PanelWidget* _energyWidget = nullptr;
	PanelWidget* _oxygenWidget = nullptr;
	PanelWidget* _fuelWidget = nullptr;
	Bitmap* _circleWithBarBmp = nullptr;
	BitmapWidget* _circleWithBar1 = nullptr;
	BitmapWidget* _circleWithBar2 = nullptr;
	BitmapWidget* _circleWithBar3 = nullptr;
	LabelWidget* _energyPercentage = nullptr;
	LabelWidget* _oxygenPercentage = nullptr;
	LabelWidget* _fuelPercentage = nullptr;
	LabelWidget* _energyTextLeft = nullptr;
	LabelWidget* _oxygenTextLeft = nullptr;
	LabelWidget* _fuelTextLeft = nullptr;
	LabelWidget* _energyTextRight = nullptr;
	LabelWidget* _oxygenTextRight = nullptr;
	LabelWidget* _fuelTextRight = nullptr;


	// topLeftPanel
	PanelWidget* _topLeftPanel = nullptr;
	Bitmap* _mapBmp = nullptr;
	Bitmap* _mapShipBmp = nullptr;
	BitmapWidget* _map = nullptr;
	BitmapWidget* _mapShip = nullptr;

	//bottomRightPanel
	PanelWidget* _bottomRightPanel = nullptr;
	std::vector<Bitmap*> _circleBmpVector;
	std::vector<BitmapWidget*> _circleVector;
	std::vector<LabelWidget*> _weaponLabelVector;
	std::vector<LabelWidget*> _weaponAmmoVector;
	std::vector<PanelWidget*> _weaponVector;

	void createHUD();
	void drawHud(Graphics* g);
};
