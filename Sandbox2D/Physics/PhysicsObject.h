#pragma once

#include "../../stdafx.h"

class ContactListener;

/**
* \brief PhysicsObject
*/
class PhysicsObject
{
public:
	/**
	* \brief Constructor
	* \n Creates a physics object and adds it's Box2D body to the game world
	* @param pos: a Vector2 object
	* @param angle: a double
	* @param bodyType: a bodyType object
	*/
	PhysicsObject(Vector2 pos, double angle, BodyType bodyType);

	/**
	* \brief Destructor
	*/
	virtual ~PhysicsObject();

	/**
	* \brief Gets the body
	* @return _bodyPtr
	*/
	b2Body* getBody() { return _bodyPtr; }

	// Add fixtures

	/**
	* \brief Adds a rectangular fixture to the object
	* @param size: a Vector2 object
	* @param restitution: a double (default = 0.8)
	* @param friction: a double (default = 0.7)
	* @param density: a double (default = 1)
	* @return A b2Fixture pointer
	*/
	b2Fixture* addBoxFixture(Vector2 size, double restitution = 0.8, double friction = 0.7, double density = 1);
	//! Adds a circular fixture to the object

	/**
	* \brief Adds a circular fixture to the object
	* @param radius: a double
	* @param offset: a Vector2 object (default = Vector2{ 0, 0 })
	* @param restitution: a double (default = 0.8)
	* @param friction: a double (default = 0.7)
	* @param density: a double (default = 1)
	* @return A b2Fixture pointer
	*/
	b2Fixture* addCircleFixture(double radius, Vector2 offset = Vector2{ 0, 0 }, double restitution = 0.8, double friction = 0.7, double density = 1);

	/**
	* \brief Adds a polygonal fixture to the object
	* @param vertexArr: a reference of a Poly<Vector2> object
	* @param restitution: a double (default = 0.8)
	* @param friction: a double (default = 0.7)
	* @param density: a double (default = 1)
	* @return A b2Fixture pointer
	*/
	b2Fixture* addPolygonFixture(const Poly<Vector2> &vertexArr, double restitution = 0.8, double friction = 0.7, double density = 1);

	/**
	* \brief Adds a chain fixture to the object
	* @param vertexArr: a reference of a Poly<Vector2> object
	* @param closed: a boolean
	* @param restitution: a double (default = 0.8)
	* @param friction: a double (default = 0.7)
	* @param density: a double (default = 1)
	* @return A b2Fixture pointer
	*/
	b2Fixture* addChainFixture(Poly<Vector2> &vertexArr, bool closed, double restitution = 0.8, double friction = 0.7, double density = 1);

	// Getter/Setter wrappers

	/**
	* \brief Gets the object's position
	* @return A Vector2 object
	*/
	Vector2 getPosition() const;

	/**
	* \brief Sets the object's position (teleport)
	* @param newPos: a reference of a Vector2 object
	*/
	void setPosition(const Vector2& newPos) const;

	/**
	* \brief Gets the object's angle in radians
	* @return A double
	*/
	double getAngleRad() const;

	/**
	* \brief Gets the object's angle in degrees
	* @return A double
	*/
	double getAngleDeg() const;

	/**
	* \brief Sets the object's angle in radians
	* @param newAngle: a double in radians
	*/
	void setAngleRad(double newAngle) const;
	
	/**
	* \brief Sets the object's angle in degrees
	* @param newAngle: a double in degrees
	*/
	void setAngleDeg(double newAngle) const;

	/**
	* \brief Apply a torque to the object
	* @param torque: a double
	*/
	void applyTorque(double torque) const;

	/**
	* \brief Gets the object's current linear velocity
	* @return A Vector2 object
	*/
	Vector2 getLinearVelocity() const;

	/**
	* \brief Sets the object's linear velocity
	* @param newVelocity: a reference of a Vector2 object
	*/
	void setLinearVelocity(const Vector2& newVelocity) const;

	/**
	* \brief Sets the amount of energy lost each physicsStep
	* @param dampening: a double
	*/
	void setLinearDamping(double dampening) const;

	/**
	* \brief Gets the object's current linear damping
	* @return A double
	*/
	double getLinearDamping() const;

	/**
	* \brief Applies a sudden impulse to the object
	* @param impulse: a Vector2 object
	*/
	void applyLinearImpulse(Vector2 impulse) const;

	/**
	* \brief Applies a gradual force to the object
	* @param force: a Vector2 object
	*/
	void applyForce(Vector2 force) const;

	/**
	* \brief Gets the object's current angular velocity
	* @return A double
	*/
	double getAngularVelocity() const;

	/**
	* \brief Sets the object's angular velocity
	* @param newVelocity: a double
	*/
	void setAngularVelocity(const double newVelocity) const;

	/**
	* \brief Gets the object's current angular damping
	* @return A double
	*/
	double getAngularDamping() const;

	/**
	* \brief Sets the amount of angular momentum lost each physicsStep
	* @param dampening: a double
	*/
	void setAngularDamping(double dampening) const;

	/**
	* \brief Locks the angular rotation
	* \n Object can still be rotated with setAngle(...)
	* @param newFixedRotation: a boolean
	*/
	void setFixedRotation(bool newFixedRotation) const;

	/**
	* \brief Returns true if the objec's angular rotation is locked
	* @return True if the object's angular rotation is locked
	*/
	bool isFixedRotation() const;

	/**
	* \brief Add this object to the contactlistener. This must be an object of a class that is derived from the ContactListener Class
	* \n Contacts with this actor will be reported in BeginContact or EndContact
	* @param listenerPtr: pointer to a ContactListener
	*/
	void addContactListener(ContactListener *listenerPtr) const;
	
	/**
	* \brief Remove this actor object from the contactlistener
	* \n Contacts with this actor will no longer be reported in BeginContact or EndContact
	*/
	void removeContactListener() const;

	/**
	* \brief Disables movement of the actor to save some CPU processing time
	* @param newAwake: a boolean
	*/
	void setAwake(bool newAwake) const;

	/**
	* \brief Returns true if the object is awake
	* @return True if the object is awake
	*/
	bool isAwake() const;

	/**
	* \brief Increases the amount of physics steps, also increases processing time
	* \n Only set to true in small, fast moving objects
	* @param newBullet: a boolean
	*/
	void setBullet(bool newBullet) const;

	/**
	* \brief Returns true if the object is a bullet
	* @return True if the object is a bullet
	*/
	bool isBullet() const;

	//! const double _box2DScale
	const double _box2DScale = 100.0;

	//! int _userData
	int _userData = 0;

	//! void *_userDataPtr
	void *_userDataPtr = nullptr;
private:
	/**
	* \brief Create a body
	* @param pos: a Vector2 object
	* @param angle: a double
	* @param bodyType: a BodyType object
	* @return A pointer to a b2Body object
	*/
	b2Body* createBody(Vector2 pos, double angle, BodyType bodyType) const;

	//! b2Body* _bodyPtr
	b2Body* _bodyPtr = nullptr;

	//! b2Filter _collisionFilter
	b2Filter _collisionFilter;

	//! bool _isSensor
	bool _isSensor = false;
};
