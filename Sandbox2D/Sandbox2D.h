#pragma once

#include "../stdafx.h"

//class GameState;
class PrecisionTimer;
class InputManager;
struct Graphics;

class Sandbox2D : public b2ContactListener, public b2DestructionListener
{
private:
	Sandbox2D();
	static Sandbox2D* _sandbox2DPtr;
	virtual ~Sandbox2D();

	void init();

	// Private datamembers
	// Engine specific
	PrecisionTimer* _gameTickTimerPtr = nullptr;

	Cache*			_cache = nullptr;
	std::vector<GameState*> _states;

	//! Box2D/physics
	b2World* _box2DWorld;
	double	_physicsTimeStep = 1 / 144.0; // cap FPS to run sync with physics
	Vector2 _gravity;
public:
	// C++11 make class non-copyable
	Sandbox2D(const Sandbox2D&) = delete;
	Sandbox2D& operator=(const Sandbox2D&) = delete;

	//! Get the pointer to the Sandbox2D singleton
	static Sandbox2D* GetSingleton();

	//! Public functions used by main.cpp,
	//! Using this outside of main.cpp will result in undefined beheaviour
	int run();
	//! Public functions used by main.cpp,
	//! Using this outside of main.cpp will result in undefined beheaviour
	void destroy();

	// Gamestates

	//! Changes to a new gamestate
	void changeState(GameState* state);
	//! Adds a new gamestate to the stack
	void pushState(GameState* state);
	//! Pops the last gamestate
	void popState();

	// Cache helpers

	//! Gets the _cache object. Do not use unless you know what you are doing
	Cache* getCache() const;
	//! Create a _bitmap in _cache
	void bitmapToCache(std::string name, std::string path) const;
	//! Create a font in _cache
	void fontToCache(std::string name, std::string path, int size) const;

	// Box2D helpers
	b2World* getb2World() const
	{
		return _box2DWorld;
	}
	void setGravity(const Vector2 gravity) 
	{ 
		_gravity = gravity; 
		_box2DWorld->SetGravity(Tob2Vec2(gravity)); 
	}

	// Box2D overloads
	// Box2D virtual overloads
	void BeginContact(b2Contact* contactPtr) override;
	void EndContact(b2Contact* contactPtr) override;
	void PreSolve(b2Contact* contactPtr, const b2Manifold* oldManifoldPtr) override;
	void PostSolve(b2Contact* contactPtr, const b2ContactImpulse* impulsePtr) override {};
	void SayGoodbye(b2Joint* jointPtr) override;
	void SayGoodbye(b2Fixture* fixturePtr) override;

	// Public datamembers
	
	//! Handles all keyboard and mouse input
	InputManager* _inputManager = nullptr;
	//! Handles all drawing functions
	Graphics* _graphics = nullptr;

	//! Amount of velocity iterations. 
	//! Higher = more accurate velocity changes = more processing time per tick
	int _velocityIterations = 6;
	//! Amount of position iterations
	//! Higher = more accurate positioning = more processing time per tick
	int _positionIterations = 2;
};