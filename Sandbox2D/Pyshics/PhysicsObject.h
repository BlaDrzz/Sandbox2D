#pragma once
#include "../../stdafx.h"

class PhysicsObject
{
public:
	Vector2 _position;
	Vector2 _velocity;
	double _restitution;
	double _mass;

	PhysicsObject(Vector2 position);
	~PhysicsObject();
};

