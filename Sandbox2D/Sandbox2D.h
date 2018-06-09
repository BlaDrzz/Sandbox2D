#pragma once

//class GameState;
class PrecisionTimer;
class InputManager;
class Graphics;

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

	Graphics*		_graphics = nullptr;
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


	// Box2D helpers
	b2World* getb2World() const;
	void setGravity(const Vector2 gravity);

	// Audio
	// Globals
	static bool isMusicPlaying() { return Mix_PlayingMusic(); }
	static bool isMusicPaused() { return Mix_PausedMusic(); }

	Pixel getWindowSize() const;

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

	//! Amount of velocity iterations. 
	//! Higher = more accurate velocity changes = more processing time per tick
	int _velocityIterations = 6;
	//! Amount of position iterations
	//! Higher = more accurate positioning = more processing time per tick
	int _positionIterations = 2;
};