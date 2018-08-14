#pragma once

/**
* \brief The InputManager
*/
class InputManager
{
public:

	/**
	* \brief Destructor
	*/
	~InputManager();

	// C++11 make the class non-copyable
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	/**
	* \brief Gets the mouse position
	* @return A pixel
	*/
	Pixel getMousePos() const;
	
	/**
	* \brief Checks if a key is pressed
	* \n Scancodes can be found here: https://wiki.libsdl.org/SDLKeycodeLookup
	* @param sc: SDL_Scancode
	* @return True if a key was unpressed last frame, and is pressed now
	*/
	bool isKeyboardKeyPressed(SDL_Scancode sc) const;

	/**
	* \brief Checks if a key is down
	* \n Scancodes can be found here: https://wiki.libsdl.org/SDLKeycodeLookup
	* @param sc: SDL_Scancode
	* @return True if a key was pressed last frame, and is pressed now
	*/
	bool isKeyboardKeyDown(SDL_Scancode sc) const;

	/**
	* \brief Checks if a key is released
	* \n Scancodes can be found here: https://wiki.libsdl.org/SDLKeycodeLookup
	* @param sc: SDL_Scancode
	* @return True if a key was pressed last frame, and is unpressed now
	*/
	bool isKeyboardKeyReleased(SDL_Scancode sc) const;

	/**
	* \brief Checks if a mousebutton is pressed
	* \n SDL_BUTTON_LEFT		: Left mouse button
	* \n SDL_BUTTON_MIDDLE		: Middle mouse button
	* \n SDL_BUTTON_RIGHT		: Right mouse button
	* \n SDL_BUTTON_WHEELUP		: Mouse wheel up(may also be a real button)
	* \n SDL_BUTTON_WHEELDOWN	: Mouse wheel down(may also be a real button)
	* @param button: an integer
	* @return True if a mouse button was unpressed last frame, and is pressed now
	*/
	bool isMouseButtonPressed(int button) const;

	/**
	* \brief Checks if a mousebutton is down
	* \n SDL_BUTTON_LEFT		: Left mouse button
	* \n SDL_BUTTON_MIDDLE		: Middle mouse button
	* \n SDL_BUTTON_RIGHT		: Right mouse button
	* \n SDL_BUTTON_WHEELUP		: Mouse wheel up(may also be a real button)
	* \n SDL_BUTTON_WHEELDOWN	: Mouse wheel down(may also be a real button)
	* @param button: an integer
	* @return True if a mouse button was pressed last frame, and is pressed now
	*/
	bool isMouseButtonDown(int button) const;
 
	/**
	* \brief Checks if a mousebutton is released
	* \n SDL_BUTTON_LEFT		: Left mouse button
	* \n SDL_BUTTON_MIDDLE		: Middle mouse button
	* \n SDL_BUTTON_RIGHT		: Right mouse button
	* \n SDL_BUTTON_WHEELUP		: Mouse wheel up(may also be a real button)
	* \n SDL_BUTTON_WHEELDOWN	: Mouse wheel down(may also be a real button)
	* @param button: an integer
	* @return True if a mouse button was pressed last frame, and is unpressed now
	*/
	bool isMouseButtonReleased(int button) const;

private:
	/**
	* \brief A friend class Sandbox2D
	*/
	friend class Sandbox2D;

	/**
	* \brief Constructor
	*/
	InputManager();

	/**
	* \brief const Uint8* _currKeyboardState
	*/
	const Uint8* _currKeyboardState;

	/**
	* \brief Uint8* _oldKeyboardState
	*/
	Uint8* _oldKeyboardState;

	/**
	* \brief int _keyboardStateLength
	*/
	int _keyboardStateLength;

	/**
	* \brief Uint32 _currMouseState
	*/
	Uint32 _currMouseState;

	/**
	* \brief Uint32 _oldMouseState
	*/
	Uint32 _oldMouseState;

	/**
	* \brief Pixel _mouseLocation
	*/
	Pixel _mouseLocation;

	/**
	* \brief sets the old input states
	*/
	void setOldInputStates();

	/**
	* \brief sets the current input states
	*/
	void setCurrInputStates();
};
