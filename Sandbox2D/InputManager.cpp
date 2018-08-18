#include "../stdafx.h"

InputManager::InputManager()
{
	_currKeyboardState = SDL_GetKeyboardState(&_keyboardStateLength);
	_oldKeyboardState = new Uint8[_keyboardStateLength];

	_currMouseState = SDL_GetMouseState(&_mouseLocation.x, &_mouseLocation.y);
	_oldMouseState = _currMouseState;
}

InputManager::~InputManager()
{
	delete[] _oldKeyboardState;
	_oldKeyboardState = nullptr;
}

Pixel InputManager::getMousePos() const
{
	return _mouseLocation;
}

void InputManager::setOldInputStates()
{
	// Set current states to old states
	memcpy(_oldKeyboardState, _currKeyboardState, _keyboardStateLength);
	_oldMouseState = _currMouseState;
}

void InputManager::setCurrInputStates()
{
	// Fill up new states
	_currKeyboardState = SDL_GetKeyboardState(nullptr);
	_currMouseState = SDL_GetMouseState(&_mouseLocation.x, &_mouseLocation.y);
}

bool InputManager::isKeyboardKeyPressed(SDL_Scancode sc) const
{
	return (!_oldKeyboardState[sc] && _currKeyboardState[sc]);
}

bool InputManager::isKeyboardKeyDown(SDL_Scancode sc) const
{
	return (_oldKeyboardState[sc] && _currKeyboardState[sc]);
}

bool InputManager::isKeyboardKeyReleased(SDL_Scancode sc) const
{
	return (_oldKeyboardState[sc] && !_currKeyboardState[sc]);
}

bool InputManager::isMouseButtonPressed(int button) const
{
	return (!(_oldMouseState & SDL_BUTTON(button)) && (_currMouseState & SDL_BUTTON(button)));
}

bool InputManager::isMouseButtonDown(int button) const
{
	return ((_oldMouseState & SDL_BUTTON(button)) && (_currMouseState & SDL_BUTTON(button)));
}

bool InputManager::isMouseButtonReleased(int button) const
{
	return ((_oldMouseState & SDL_BUTTON(button)) && !(_currMouseState & SDL_BUTTON(button)));
}
