#pragma once
class InputManager
{
public:
	~InputManager();

	// C++11 make the class non-copyable
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	Pixel getMousePos() const;
	

	//! Returns true if a key was unpressed last frame, and is pressed now
	//! Scancodes can be found here: https://wiki.libsdl.org/SDLKeycodeLookup
	bool isKeyboardKeyPressed(SDL_Scancode sc) const;
	//! Returns true if a key was pressed last frame, and is pressed now
	//! Scancodes can be found here: https://wiki.libsdl.org/SDLKeycodeLookup
	bool isKeyboardKeyDown(SDL_Scancode sc) const;
	//! Returns true if a key was pressed last frame, and is unpressed now
	//! Scancodes can be found here: https://wiki.libsdl.org/SDLKeycodeLookups
	bool isKeyboardKeyReleased(SDL_Scancode sc) const;

	//! Returns true if a mouse button was unpressed last frame, and is pressed now
	//! SDL_BUTTON_LEFT		 : Left mouse button
	//! SDL_BUTTON_MIDDLE	 : Middle mouse button
	//! SDL_BUTTON_RIGHT	 : Right mouse button
	//! SDL_BUTTON_WHEELUP	 : Mouse wheel up(may also be a real button)
	//! SDL_BUTTON_WHEELDOWN : Mouse wheel down(may also be a real button)
	bool isMouseButtonPressed(int button) const;
	//! Returns true if a mouse button was pressed last frame, and is pressed now
	//! SDL_BUTTON_LEFT		 : Left mouse button
	//! SDL_BUTTON_MIDDLE	 : Middle mouse button
	//! SDL_BUTTON_RIGHT	 : Right mouse button
	//! SDL_BUTTON_WHEELUP	 : Mouse wheel up(may also be a real button)
	//! SDL_BUTTON_WHEELDOWN : Mouse wheel down(may also be a real button)
	bool isMouseButtonDown(int button) const;
	//! Returns true if a mouse button was pressed last frame, and is unpressed now
	//! SDL_BUTTON_LEFT		 : Left mouse button
	//! SDL_BUTTON_MIDDLE	 : Middle mouse button
	//! SDL_BUTTON_RIGHT	 : Right mouse button
	//! SDL_BUTTON_WHEELUP	 : Mouse wheel up(may also be a real button)
	//! SDL_BUTTON_WHEELDOWN : Mouse wheel down(may also be a real button)
	bool isMouseButtonReleased(int button) const;

private:
	friend class Sandbox2D;
	InputManager();

	// Keyboard
	const Uint8* _currKeyboardState;
	Uint8* _oldKeyboardState;
	int _keyboardStateLength;

	// Mouse
	Uint32 _currMouseState;
	Uint32 _oldMouseState;
	Pixel _mouseLocation;

	void setOldInputStates();
	void setCurrInputStates();
};
