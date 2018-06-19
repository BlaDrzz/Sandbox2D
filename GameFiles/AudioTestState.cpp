// Include files
#include "../stdafx.h"
#include "AudioTestState.h"

// Defines
#define S2D (Sandbox2D::GetSingleton())

// AudioTestState methods
AudioTestState::AudioTestState() {}
AudioTestState::~AudioTestState() {}

void AudioTestState::stateStart()
{
	// Executed at start of state
	
	// Load music
	_music = new Music("Resources/beat.wav");

	// Load sound
	_scratch = new SoundFX("Resources/scratch.wav");
}

void AudioTestState::stateEnd()
{
	// Executed at end of state

}

void AudioTestState::stateTick(double deltaTime) 
{
	// Executed each game tick, game logic goes here

	if (S2D->_inputManager->isKeyboardKeyPressed(SDL_SCANCODE_Z)) _scratch->play();

	if (S2D->_inputManager->isKeyboardKeyPressed(SDL_SCANCODE_M))
	{
		//If there is no music playing
		if (!S2D->isMusicPlaying()) _music->start();
		else
		{
			// Music is paused?
			if (S2D->isMusicPaused()) _music->resume();
			else _music->pause();
		}
	}

}

void AudioTestState::statePaint(Graphics* g)
{
	// Executed after game tick, game drawing calls go 
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void AudioTestState::beginContact(PhysicsObject* actThisPtr, PhysicsObject* actOtherPtr)
{
}

void AudioTestState::endContact(PhysicsObject* actThisPtr, PhysicsObject* actOtherPtr)
{
}

void AudioTestState::contactImpulse(PhysicsObject* actThisPtr, double impulse)
{
}	