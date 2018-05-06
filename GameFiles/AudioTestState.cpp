#pragma once

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
	
	// Load the music
	_music = Mix_LoadMUS("Resources/beat.wav");
	if (_music == nullptr) Log("Something went wrong!");

	//Load the sound effects
	_scratch = Mix_LoadWAV("Resources/scratch.wav");
	_high = Mix_LoadWAV("Resources/high.wav");
	_med = Mix_LoadWAV("Resources/medium.wav");
	_low = Mix_LoadWAV("Resources/low.wav");
}

void AudioTestState::stateEnd()
{
	// Executed at end of state

	// Free the music
	Mix_FreeMusic(_music);

	// Free the sound effects
	Mix_FreeChunk(_scratch);
	Mix_FreeChunk(_high);
	Mix_FreeChunk(_med);
	Mix_FreeChunk(_low);
}

void AudioTestState::stateTick(double deltaTime) 
{
	// Executed each game tick, game logic goes here

	if (S2D->_inputManager->isKeyboardKeyPressed(SDL_SCANCODE_Z)) Mix_PlayChannel(-1, _scratch, 0);
	if (S2D->_inputManager->isKeyboardKeyPressed(SDL_SCANCODE_X)) Mix_PlayChannel(-1, _high, 0);
	if (S2D->_inputManager->isKeyboardKeyPressed(SDL_SCANCODE_C)) Mix_PlayChannel(-1, _med, 0);
	if (S2D->_inputManager->isKeyboardKeyPressed(SDL_SCANCODE_V)) Mix_PlayChannel(-1, _low, 0);

	if (S2D->_inputManager->isKeyboardKeyPressed(SDL_SCANCODE_M))
	{
		//If there is no music playing
		if (Mix_PlayingMusic() == 0) Mix_PlayMusic(_music, -1);
		else
		{
			// Music is paused?
			if (Mix_PausedMusic() == 1) Mix_ResumeMusic();
			else Mix_PauseMusic();
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