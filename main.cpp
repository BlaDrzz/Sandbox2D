#pragma once

#include "stdafx.h"

#ifdef _WIN32
// Memory management
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

// Implictly creates the S2D singleton if it does not exist already; returns it
#define S2D (Sandbox2D::GetSingleton())

int main(int argc, char* args[]) 
{
#ifdef _WIN32
	// Memory management
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// Create engine
	if (S2D == nullptr) return 1; // There was an error creating the Sandbox2D object.

	// run main cycle
	const auto returnValue = S2D->run();

	// destroy EntryState
	S2D->destroy();

	// Give user time to read console for errors
	const Uint32 delay = 1; // Delay in seconds
	printf("This window will automatically close in %d seconds...", delay);
	SDL_Delay(delay * 1000); 

	return returnValue;
}