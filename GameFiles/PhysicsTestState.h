#pragma once

// Include files
#include "../Sandbox2D/GameState.h"

// Forward Declarations

// PhysicsTestState class
class PhysicsTestState : public GameState, public ContactListener
{
public:
	// Constructor
	PhysicsTestState();
	virtual ~PhysicsTestState();

	// C++11 make class non-copyable
	PhysicsTestState(const PhysicsTestState&) = delete;
	PhysicsTestState& operator=(const PhysicsTestState&) = delete;

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
	PhysicsObject* _poTestObj2 = nullptr;
	Bitmap* _bmpTest = nullptr;
};