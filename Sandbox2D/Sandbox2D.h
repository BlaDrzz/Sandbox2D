#pragma once


//class GameState;
class PrecisionTimer;
class InputManager;
class Graphics;
class GlobalState;

/**
* \brief Represents the Sandbox2D
*/
class Sandbox2D : public b2ContactListener, public b2DestructionListener
{
private:
	/**
	* \brief Constructor
	*/
	Sandbox2D();

	/**
	* \brief static Sandbox2D* _sandbox2DPtr
	*/
	static Sandbox2D* _sandbox2DPtr;

	/**
	* \brief Destructor
	*/
	virtual ~Sandbox2D();

	/**
	* \brief Initialize
	*/
	void init();

	// Private datamembers
	// Engine specific

	/**
	* \brief PrecisionTimer* _gameTickTimerPtr
	*/
	PrecisionTimer* _gameTickTimerPtr = nullptr;

	/**
	* \brief Graphics* _graphics
	*/
	Graphics*		_graphics = nullptr;

	/**
	* \brief std::vector<GameState*> _states
	*/
	std::vector<GameState*> _states;

	//! Box2D/physics

	/**
	* \brief b2World* _box2DWorld
	*/
	b2World* _box2DWorld;

	/**
	* \brief double	_physicsTimeStep
	*/
	double	_physicsTimeStep = 1 / 144.0; // cap FPS to run sync with physics
	
	/**
	* \brief Vector2 _gravity
	*/
	Vector2 _gravity;
public:
	// C++11 make class non-copyable
	Sandbox2D(const Sandbox2D&) = delete;
	Sandbox2D& operator=(const Sandbox2D&) = delete;

	/**
	* \brief Gets the pointer to the Sandbox2D singleton
	* @return A pointer to the Sandbox2D singleton
	*/
	static Sandbox2D* GetSingleton();

	/**
	* \brief Public functions used by main.cpp
	* \n Using this outside of main.cpp will result in undefined behaviour
	*/
	int run();
	
	/**
	* \brief Public functions used by main.cpp
	* \n Using this outside of main.cpp will result in undefined behaviour
	*/
	void destroy();

	// Gamestates

	/**
	* \brief Changes to a new game state
	* @param state: pointer to a new game state
	*/
	void changeState(GameState* state);
	
	/**
	* \brief Adds a new game state to the stack
	* @param state: pointer to a new game state
	*/
	void pushState(GameState* state);
	
	/**
	* \brief Pops the last game state
	*/
	void popState();

	// Box2D helpers
	/**
	* \brief Get a pointer to a b2World
	* @return a pointer to a b2World
	*/
	b2World* getb2World() const;

	/**
	* \brief Sets the gravity
	* @param gravity: gravity as a Vector2 object
	*/
	void setGravity(Vector2 gravity);

	// Audio
	// Globals
	/**
	* \brief Checks if music is playing
	* @return A boolean
	*/
	static bool isMusicPlaying() { return Mix_PlayingMusic(); }

	/**
	* \brief Checks if music is paused
	* @return A boolean
	*/
	static bool isMusicPaused() { return Mix_PausedMusic(); }

	/**
	* \brief Gets the window size
	* @return A Pixel
	*/
	Pixel getWindowSize() const;

	// Box2D overloads
	// Box2D virtual overloads
	/**
	* \brief Begin contact
	* @param contactPtr: b2Contact pointer
	*/
	void BeginContact(b2Contact* contactPtr) override;

	/**
	* \brief End contact
	* @param contactPtr: b2Contact pointer
	*/
	void EndContact(b2Contact* contactPtr) override;

	/**
	* \brief Pre Solve
	* @param contactPtr: b2Contact pointer
	* @param oldManifoldPtr: b2Manifold pointer
	*/
	void PreSolve(b2Contact* contactPtr, const b2Manifold* oldManifoldPtr) override;

	/**
	* \brief Post Solve
	* @param contactPtr: b2Contact pointer
	* @param impulsePtr: b2ContactImpulse pointer
	*/
	void PostSolve(b2Contact* contactPtr, const b2ContactImpulse* impulsePtr) override {};
	
	/**
	* \brief Say Goodbye
	* @param jointPtr: b2Joint pointer
	*/
	void SayGoodbye(b2Joint* jointPtr) override;

	/**
	* \brief Say Goodbye
	* @param fixturePtr: b2Fixture pointer
	*/
	void SayGoodbye(b2Fixture* fixturePtr) override;

	// Public datamembers

	//! Global State which runs all the time. \n
	//! Global stateStart is executed BEFORE the active state stateStart, \n
	//! Global stateEnd is executed AFTER the active state stateEnd, \n
	//! Global stateTick is executed BEFORE the active state stateTick.
	GlobalState* globalState = nullptr;
	
	//! Handles all keyboard and mouse input
	InputManager* inputManager = nullptr;

	//! Amount of velocity iterations. 
	//! Higher = more accurate velocity changes = more processing time per tick
	int velocityIterations = 6;

	//! Amount of position iterations
	//! Higher = more accurate positioning = more processing time per tick
	int positionIterations = 2;
};