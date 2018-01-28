#pragma once

class PhysicsObject;

class ContactListener
{
public:
	ContactListener() {}
	virtual ~ContactListener() {}

	virtual void beginContact(PhysicsObject* objThis, PhysicsObject* objOther) {}
	virtual void endContact(PhysicsObject* objThis, PhysicsObject* objOther) {}
	virtual void contactImpulse(PhysicsObject* objThis, double impulse) {}
	virtual void preSolve(PhysicsObject* objThis, PhysicsObject* objOther, bool &enableContactRef) {}
};
