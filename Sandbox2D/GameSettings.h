#pragma once

/**
* \brief Represents the game settings
*/
struct GameSettings
{
	/**
	* \brief The window size
	*/
	Pixel _windowSize = { 842, 480 };

	/**
	* \brief The title of the window
	*/
	std::string _windowTitle = "An S2D game";
};