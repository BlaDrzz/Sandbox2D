#include "PhysicsObject.h"

#define S2D (Sandbox2D::GetSingleton())

PhysicsObject::PhysicsObject(const Vector2 pos, const double angle, const BodyType bodyType)
{
	_bodyPtr = createBody(pos, angle, bodyType);
}


PhysicsObject::~PhysicsObject()
{
	// Clean fixture's userdata
	for (auto fixture = _bodyPtr->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext())
	{
		fixture->SetUserData(nullptr);
	}

	// Remove object from the game's world
	S2D->getb2World()->DestroyBody(_bodyPtr);
	_bodyPtr = nullptr;
}

b2Fixture* PhysicsObject::addBoxFixture(const Vector2 size, const double restitution, 
										const double friction, const double density)
{
	// Resize to box2D units
	const auto width = size.x / scale;
	const auto height = size.y / scale;

	// Create shape
	b2PolygonShape shape;
	shape.SetAsBox(float(width / 2), float(height / 2));

	// Build fixture definition
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.restitution = float(restitution);
	if (_bodyPtr->GetType() == b2_dynamicBody) fixtureDef.density = float(density);
	else fixtureDef.density = 0.0f;

	fixtureDef.friction = float(friction);
	fixtureDef.userData = static_cast<void*>(this);
	fixtureDef.filter = _collisionFilter;

	// Create fixture
	auto* fixture = _bodyPtr->CreateFixture(&fixtureDef);
	if (fixture != nullptr) fixture->SetSensor(_isSensor);

	return fixture;
}

b2Fixture* PhysicsObject::addCircleFixture(double radius, Vector2 offset, const double restitution,
                                           const double friction, const double density)
{
	// Resize to box2D units
	radius /= scale;
	offset = { offset.x / scale, offset.y / scale };

	// Create shape
	b2CircleShape circle;
	circle.m_p.Set(float(offset.x), float(offset.y));
	circle.m_radius = float(radius);

	// Build fixture definition
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.restitution = float(restitution);
	if (_bodyPtr->GetType() == b2_dynamicBody) fixtureDef.density = float(density);
	else fixtureDef.density = 0.0f;

	fixtureDef.friction = float(friction);
	fixtureDef.userData = static_cast<void*>(this);
	fixtureDef.filter = _collisionFilter;

	// Create fixture
	auto* fixture = _bodyPtr->CreateFixture(&fixtureDef);
	if (fixture != nullptr) fixture->SetSensor(_isSensor);

	return fixture;
}

b2Fixture* PhysicsObject::addPolygonFixture(const Poly<Vector2>& vertexArr, const double restitution,
                                            const double friction, const double density)
{
	// Convert and resize to box2D units
	std::vector<b2Vec2> vecArr;
	for (const auto vec2 : vertexArr)
		vecArr.push_back(b2Vec2(float(vec2.x / scale), float(vec2.y / scale)));

	// Create shape
	b2PolygonShape polyShape;
	polyShape.Set(vecArr.data(), vecArr.size());

	// Build fixture definition
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polyShape;
	fixtureDef.restitution = float(restitution);
	if (_bodyPtr->GetType() == b2_dynamicBody) fixtureDef.density = float(density);
	else fixtureDef.density = 0.0f;

	fixtureDef.friction = float(friction);
	fixtureDef.userData = static_cast<void*>(this);
	fixtureDef.filter = _collisionFilter;

	// Create fixture
	auto* fixture = _bodyPtr->CreateFixture(&fixtureDef);
	if (fixture != nullptr) fixture->SetSensor(_isSensor);

	return fixture;
}

b2Fixture* PhysicsObject::addChainFixture(Poly<Vector2>& vertexArr, const bool closed, const double restitution,
                                          const double friction, const double density)
{
	// If last is too close to start, delete last. Points too close to eachother can cause a Box2D crash
	if (Distance(vertexArr.front(), vertexArr.back()) < 0.1) vertexArr.pop_back();

	// Convert and resize to box2D units
	std::vector<b2Vec2> vecArr;
	for (const auto vec2 : vertexArr)
		vecArr.push_back(b2Vec2(float(vec2.x / scale), float(vec2.y / scale)));

	// Create shape
	b2ChainShape chainShape;
	if (closed) chainShape.CreateLoop(vecArr.data(), vecArr.size());
	else chainShape.CreateChain(vecArr.data(), vecArr.size());

	// Build fixture definition
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &chainShape;
	fixtureDef.restitution = float(restitution);
	if (_bodyPtr->GetType() == b2_dynamicBody) fixtureDef.density = float(density);
	else fixtureDef.density = 0.0f;

	fixtureDef.friction = float(friction);
	fixtureDef.userData = static_cast<void*>(this);
	fixtureDef.filter = _collisionFilter;

	// Create fixture
	auto* fixture = _bodyPtr->CreateFixture(&fixtureDef);
	if (fixture != nullptr) fixture->SetSensor(_isSensor);

	return fixture;
}

Vector2 PhysicsObject::getPosition() const
{
	const auto pos = _bodyPtr->GetPosition();
	return{ pos.x * scale, pos.y * scale };
}

void PhysicsObject::setPosition(const Vector2& newPos) const
{
	_bodyPtr->SetTransform(
		b2Vec2(float(newPos.x / scale),
			float(newPos.y / scale)),
		_bodyPtr->GetAngle()
	);
	_bodyPtr->SetAwake(true);
}

double PhysicsObject::getAngle() const
{
	return _bodyPtr->GetAngle();
}

void PhysicsObject::setAngle(const double newAngle) const
{
	_bodyPtr->SetTransform(_bodyPtr->GetPosition(), float(newAngle));
	_bodyPtr->SetAwake(true);
}

Vector2 PhysicsObject::getLinearVelocity() const
{
	const auto vel = _bodyPtr->GetLinearVelocity();
	return{ vel.x * scale, vel.y * scale };
}

void PhysicsObject::setLinearVelocity(const Vector2& newVelocity) const
{
	_bodyPtr->SetLinearVelocity(b2Vec2(float(newVelocity.x / scale), float(newVelocity.y / scale)));
	_bodyPtr->SetAwake(true);
}

double PhysicsObject::getAngularVelocity() const
{
	return _bodyPtr->GetAngularVelocity();
}

void PhysicsObject::setAngularVelocity(const double newVelocity) const
{
	_bodyPtr->SetAngularVelocity(float(newVelocity));
	_bodyPtr->SetAwake(true);
}

void PhysicsObject::addContactListener(ContactListener* listenerPtr) const
{
	_bodyPtr->SetUserData(static_cast<void*>(listenerPtr));
}

void PhysicsObject::removeContactListener() const
{
	_bodyPtr->SetUserData(nullptr);
}

b2Body* PhysicsObject::createBody(Vector2 pos, const double angle, const BodyType bodyType) const
{
	b2BodyDef bodyDef;

	switch (bodyType)
	{
	case BodyType::DYNAMIC:
		bodyDef.type = b2_dynamicBody;
		break;
	case BodyType::STATIC:
		bodyDef.type = b2_staticBody;
		break;
	case BodyType::KINEMATIC:
		bodyDef.type = b2_kinematicBody;
		break;
	}

	pos = { pos.x / scale, pos.y / scale };

	bodyDef.position.Set(float(pos.x), float(pos.y));
	bodyDef.angle = float(angle);

	return S2D->getb2World()->CreateBody(&bodyDef);
}
