#pragma once

#include "../../stdafx.h"

class ContactListener;

class PhysicsObject
{
public:
	//! creates a physics object and adds it's Box2D body to the game world
	PhysicsObject(Vector2 pos, double angle, BodyType bodyType);

	virtual ~PhysicsObject();

	//! Get the Box2D body
	b2Body* getBody() { return _bodyPtr; }

	// Add fixtures

	//! Adds a rectangular fixture to the object
	b2Fixture* addBoxFixture(Vector2 size, double restitution = 0.8, double friction = 0.7, double density = 1);
	//! Adds a circular fixture to the object
	b2Fixture* addCircleFixture(double radius, Vector2 offset = Vector2{ 0, 0 }, double restitution = 0.8, double friction = 0.7, double density = 1);
	//! Adds a polygonal fixture to the object
	b2Fixture* addPolygonFixture(const Poly<Vector2> &vertexArr, double restitution = 0.8, double friction = 0.7, double density = 1);
	//! Adds a chain fixture to the object
	b2Fixture* addChainFixture(Poly<Vector2> &vertexArr, bool closed, double restitution = 0.8, double friction = 0.7, double density = 1);

	// Getter/Setter wrappers

	//! Gets the object's position
	Vector2 getPosition() const;
	//! Sets the object's position (teleport)
	void setPosition(const Vector2& newPos) const;

	//! Gets the object's angle
	double getAngle() const;
	//! Sets the object's angle
	void setAngle(const double newAngle) const;

	//! Gets the object's current linear velocity
	Vector2 getLinearVelocity() const;
	//! Sets the object's linear velocity
	void setLinearVelocity(const Vector2& newVelocity) const;

	//! Gets the object's current angular velocity
	double getAngularVelocity() const;
	//! Sets the object's angular velocity
	void setAngularVelocity(const double newVelocity) const;

	//! add this object to the contactlistener. This must be an object of a class that is derived from the ContactListener Class
	//! contacts with this actor will be reported in BeginContact or EndContact
	void addContactListener(ContactListener *listenerPtr) const;

	//! remove this actor object from the contactlistener. 
	//! contacts with this actor will no longer be reported in BeginContact or EndContact
	void removeContactListener() const;

	static const int scale = 100;
	int _userData = 0;
	void *_userDataPtr = nullptr;
private:
	b2Body* createBody(Vector2 pos, double angle, BodyType bodyType) const;

	b2Body* _bodyPtr = nullptr;
	b2Filter _collisionFilter;

	bool _isSensor = false;
};

