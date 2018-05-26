#pragma once

// Include files
#include "../Sandbox2D/GameState.h"

// Forward Declarations

// AudioTestState class
class AudioTestState : public GameState, public ContactListener
{
public:
	// Constructor
	AudioTestState();
	virtual ~AudioTestState();

	// C++11 make class non-copyable
	AudioTestState(const AudioTestState&) = delete;
	AudioTestState& operator=(const AudioTestState&) = delete;

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
	Music* _music = nullptr;

	SoundFX* _scratch = nullptr;
};