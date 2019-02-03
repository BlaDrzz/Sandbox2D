#pragma once

// Include files
#include "../Sandbox2D/GameState.h"

// Forward Declarations

/**
* \brief EntryState
*/
class EntryState : public GameState
{
public:
	/**
	* \brief Constructor
	*/
	EntryState();

	/**
	* \brief Destructor
	*/
	virtual ~EntryState();

	// C++11 make class non-copyable
	EntryState(const EntryState&) = delete;
	EntryState& operator=(const EntryState&) = delete;

	/**
	* \brief Start entry state
	*/
	void stateStart() override;

	/**
	* \brief End entry state
	*/
	void stateEnd() override;

	/**
	* \brief State tick
	* @param deltaTime: a double
	*/
	void stateTick(double deltaTime) override;

	/**
	* \brief State paint
	* @param g: pointer to a Graphics object
	*/
	void statePaint(Graphics* g) override;

private:
	// Private functions

	// Datamembers
	ButtonWidget *_btnStart = nullptr;
};