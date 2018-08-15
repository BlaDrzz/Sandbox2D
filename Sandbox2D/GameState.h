#pragma once

class Graphics;

/**
* \brief Represents a GameState
*/
class GameState 
{
public:
	/**
	* \brief Constructor
	*/
	GameState()
	{
		// nothing to create
	}

	/**
	* \brief Destructor
	*/
	virtual ~GameState()
	{
		// nothing to destroy
	}

	// C++11 make the class non-copyable
	GameState(const GameState&) = delete;
	GameState& operator=(const GameState&) = delete;

	/**
	* \brief Start the state
	*/
	virtual void stateStart() = 0;

	/**
	* \brief Ends the state
	*/
	virtual void stateEnd() = 0;

	/**
	* \brief Executes every game tick
	*/
	virtual void stateTick(double) = 0;

	/**
	* \brief Executes after game tick, game drawing calls go 
	*/
	virtual void statePaint(Graphics*) = 0;
};