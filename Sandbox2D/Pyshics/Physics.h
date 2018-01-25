#pragma once

#include "PhysicsObject.h"

inline void ResolveCollision(PhysicsObject* a, PhysicsObject* b)
{
	const auto velA = a->_velocity;
	const auto velB = b->_velocity;
	const auto normal = Normalize(velA + velB);

	// Calcluate relative velocity
	const Vector2 relV = velB - velA;

	// Calculate relative velocity in terms of the normal direction
	const double velAlongNormal = DotProduct(relV, normal);

	// Velocities are seperating
	if (velAlongNormal > 0) return;
	
	// Calculate restitution
	const double e = MIN(a->_restitution, b->_restitution);

	// Calculate impulse scalar
	const auto massA = 1 / a->_mass;
	const auto massB = 1 / b->_mass;

	const double impulseScalar = -(1 + e) * velAlongNormal / (massA + massB);

	// Apply impulse
	const Vector2 impulse = normal * impulseScalar;

	a->_velocity = velA - impulse * massA;
	b->_velocity = velB - impulse * massB;
}