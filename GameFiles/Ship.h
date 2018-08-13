#pragma once

class Ship : public ContactListener
{
public:
	Ship(Vector2 spawnLoc);
	virtual ~Ship( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	Ship( const Ship& ) = delete;
	Ship& operator=( const Ship& ) = delete;

	double targetAngle = 0;

	void tick(double deltaTime);
	void accelerate(double deltaTime);
	void draw(Graphics* g);

	Vector2 getShipPosition() const;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	// virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	// virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	// virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);

private: 
	PhysicsObject* _shipObject = nullptr;
	double _thrusterStrength;
	double _maneuverThrustersStrength;
};
