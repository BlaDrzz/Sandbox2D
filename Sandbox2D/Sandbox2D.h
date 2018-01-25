#pragma once

class GameState;
class PrecisionTimer;
class InputManager;
struct Graphics;

class Sandbox2D 
{
private:
	Sandbox2D();
	static Sandbox2D* _sandbox2DPtr;
	virtual ~Sandbox2D();

	void init();

	// Private datamembers
	// Engine specific
	PrecisionTimer* _gameTickTimerPtr = nullptr;
	double			_maxFPS = 1 / 144.000f; // Set to 99999999.00000000000000f for practically no FPS cap
	Cache*			_cache = nullptr;
	std::vector<GameState*> _states;
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

	// Public datamembers
	// Game specific
	InputManager*	_inputManager = nullptr;
	Graphics*		_graphics = nullptr;

};