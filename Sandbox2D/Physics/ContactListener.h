#pragma once

class PhysicsObject;

/**
* \brief ContactListener
*/
class ContactListener
{
public:
	/**
	* \brief Constructor
	*/
	ContactListener() {}

	/**
	* \brief Destructor
	*/
	virtual ~ContactListener() {}

	/**
	* \brief Begin Contact
	* @param objThis: pointer to a PhysicsObject object
	* @param objOther: pointer to a PhysicsObject object
	*/
	virtual void beginContact(PhysicsObject* objThis, PhysicsObject* objOther) {}

	/**
	* \brief End Contact
	* @param objThis: pointer to a PhysicsObject object
	* @param objOther: pointer to a PhysicsObject object
	*/
	virtual void endContact(PhysicsObject* objThis, PhysicsObject* objOther) {}

	/**
	* \brief Contact Impulse
	* @param objThis: pointer to a PhysicsObject object
	* @param impulse: a double
	*/
	virtual void contactImpulse(PhysicsObject* objThis, double impulse) {}

	/**
	* \brief Pre Solve
	* @param objThis: pointer to a PhysicsObject object
	* @param objOther: pointer to a PhysicsObject object
	* @param enableContactRef: a reference of a boolean
	*/
	virtual void preSolve(PhysicsObject* objThis, PhysicsObject* objOther, bool &enableContactRef) {}
};
