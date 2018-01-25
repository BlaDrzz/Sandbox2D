#pragma once
class InputManager
{
public:
	~InputManager();

	// C++11 make the class non-copyable
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	Pixel GetMousePos() const;
	

	//! Returns true if a key was unpressed last frame, and is pressed now
	//! Scancodes can be found here: https://wiki.libsdl.org/SDLKeycodeLookup
	bool IsKeyboardKeyPressed(SDL_Scancode sc) const;
	//! Returns true if a key was pressed last frame, and is pressed now
	//! Scancodes can be found here: https://wiki.libsdl.org/SDLKeycodeLookup
	bool IsKeyboardKeyDown(SDL_Scancode sc) const;
	//! Returns true if a key was pressed last frame, and is unpressed now
	//! Scancodes can be found here: https://wiki.libsdl.org/SDLKeycodeLookups
	bool IsKeyboardKeyReleased(SDL_Scancode sc) const;

	//! Returns true if a mouse button was unpressed last frame, and is pressed now
	//! SDL_BUTTON_LEFT		 : Left mouse button
	//! SDL_BUTTON_MIDDLE	 : Middle mouse button
	//! SDL_BUTTON_RIGHT	 : Right mouse button
	//! SDL_BUTTON_WHEELUP	 : Mouse wheel up(may also be a real button)
	//! SDL_BUTTON_WHEELDOWN : Mouse wheel down(may also be a real button)
	bool IsMouseButtonPressed(int button) const;
	//! Returns true if a mouse button was pressed last frame, and is pressed now
	//! SDL_BUTTON_LEFT		 : Left mouse button
	//! SDL_BUTTON_MIDDLE	 : Middle mouse button
	//! SDL_BUTTON_RIGHT	 : Right mouse button
	//! SDL_BUTTON_WHEELUP	 : Mouse wheel up(may also be a real button)
	//! SDL_BUTTON_WHEELDOWN : Mouse wheel down(may also be a real button)
	bool IsMouseButtonDown(int button) const;
	//! Returns true if a mouse button was pressed last frame, and is unpressed now
	//! SDL_BUTTON_LEFT		 : Left mouse button
	//! SDL_BUTTON_MIDDLE	 : Middle mouse button
	//! SDL_BUTTON_RIGHT	 : Right mouse button
	//! SDL_BUTTON_WHEELUP	 : Mouse wheel up(may also be a real button)
	//! SDL_BUTTON_WHEELDOWN : Mouse wheel down(may also be a real button)
	bool IsMouseButtonReleased(int button) const;

private:
	friend class Sandbox2D;
	InputManager();

	// Keyboard
	const Uint8* m_CurrKeyboardState;
	Uint8* m_OldKeyboardState;
	int m_KeyboardStateLength;

	// Mouse
	Uint32 m_CurrMouseState;
	Uint32 m_OldMouseState;
	Pixel m_MouseLocation;

	void SetOldInputStates();
	void SetCurrInputStates();
};
