#include "../stdafx.h"		
#include "Ship.h"

// #define S2D (Sandbox2D::GetSingleton())

Ship::Ship(const Vector2 spawnLoc)
{
	_shipObject = new PhysicsObject(spawnLoc, 0, BodyType::DYNAMIC);
	_shipObject->addBoxFixture({20,20});
	_shipObject->addContactListener(this);

	_thrusterStrength = 2000;
	_maneuverThrustersStrength = 50;
	_shipObject->setLinearDamping(_maneuverThrustersStrength * 0.01);
}

Ship::~Ship()
{
	delete _shipObject;
}

void Ship::tick(const double deltaTime)
{
	// TODO: hard setting of an angle is a no-go. 
	// TODO: Consider using slerp (requires engine to be upgraded)
	_shipObject->setAngleRad(targetAngle);
}

void Ship::accelerate(const double deltaTime)
{
	_shipObject->applyForce(Vector2{
		_thrusterStrength * cos(_shipObject->getAngleRad()),
		_thrusterStrength * sin(_shipObject->getAngleRad())
	} * deltaTime);
}

void Ship::draw(Graphics* g)
{
	// Quick debug drawing
	const auto pos = getShipPosition();

	g->setColor(MakeRGBA(255,255,255));
	g->drawRect(true,
		ToPixel({ pos.x - 10, pos.y - 10 }),
		ToPixel({ pos.x + 10, pos.y + 10 })
	);

	const auto ang = _shipObject->getAngleRad();
	const auto d = 100;
	const auto pos1 = getShipPosition();
	const auto pos2 = Vector2{ pos1.x + cos(ang) * d, pos1.y + sin(ang) * d };

	g->setColor(MakeRGBA(50, 255, 0));
	g->drawLine(ToPixel(pos1), ToPixel(pos2));
}

Vector2 Ship::getShipPosition() const
{
	return _shipObject->getPosition();
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
// void Ship::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
// {
// }
// 
// void Ship::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
// {
// }
// 
// void Ship::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
// {
// }