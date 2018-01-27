#pragma once

#include "../../stdafx.h"

class PhysicsObject
{
public:
	//! Spawn position
	//! Angle of rotation
	//! BodyType Eg. BodyType::KINEMATIC
	PhysicsObject(Vector2 pos, double angle, BodyType bodyType);

	virtual ~PhysicsObject();

	//! Get the Box2D body
	b2Body* GetBody();
};

