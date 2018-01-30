#pragma once

// Include files
#include "Sandbox2D/GameState.h"

// Forward Declarations

// EntryState class
class EntryState : public GameState, public ContactListener
{
public:
	// Constructor
	EntryState();
	virtual ~EntryState();

	// C++11 make class non-copyable
	EntryState(const EntryState&) = delete;
	EntryState& operator=(const EntryState&) = delete;

	// General Methods
	void stateStart() override;
	void stateEnd() override;
	void stateTick(double deltaTime) override;
	void statePaint(Graphics* g) override;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	void beginContact(PhysicsObject *actThisPtr, PhysicsObject *actOtherPtr) override;
	void endContact(PhysicsObject *actThisPtr, PhysicsObject *actOtherPtr) override;
	void contactImpulse(PhysicsObject *actThisPtr, double impulse) override;

private:
	// Private functions

	// Datamembers
	LabelWidget* _lblInfo = nullptr;
	ButtonWidget* _btnPhysicsTestState = nullptr;

	PhysicsObject* _poTestObj = nullptr;
};