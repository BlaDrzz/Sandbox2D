#include "../stdafx.h"

InputManager::InputManager()
{
	m_CurrKeyboardState = SDL_GetKeyboardState(&m_KeyboardStateLength);
	m_OldKeyboardState = new Uint8[m_KeyboardStateLength];

	m_CurrMouseState = SDL_GetMouseState(&m_MouseLocation.x, &m_MouseLocation.y);
	m_OldMouseState = m_CurrMouseState;
}

InputManager::~InputManager()
{
	delete[] m_OldKeyboardState;
	m_OldKeyboardState = nullptr;
}

Pixel InputManager::GetMousePos() const
{
	return m_MouseLocation;
}

void InputManager::SetOldInputStates()
{
	// Set current states to old states
	std::memcpy(m_OldKeyboardState, m_CurrKeyboardState, m_KeyboardStateLength);
	m_OldMouseState = m_CurrMouseState;
}

void InputManager::SetCurrInputStates()
{
	// Fill up new states
	m_CurrKeyboardState = SDL_GetKeyboardState(nullptr);
	m_CurrMouseState = SDL_GetMouseState(&m_MouseLocation.x, &m_MouseLocation.y);
}

bool InputManager::IsKeyboardKeyPressed(SDL_Scancode sc) const
{
	return (!m_OldKeyboardState[sc] && m_CurrKeyboardState[sc]);
}

bool InputManager::IsKeyboardKeyDown(SDL_Scancode sc) const
{
	return (m_OldKeyboardState[sc] && m_CurrKeyboardState[sc]);
}

bool InputManager::IsKeyboardKeyReleased(SDL_Scancode sc) const
{
	return (m_OldKeyboardState[sc] && !m_CurrKeyboardState[sc]);
}

bool InputManager::IsMouseButtonPressed(int button) const
{
	return (!(m_OldMouseState & SDL_BUTTON(button)) && (m_CurrMouseState & SDL_BUTTON(button)));
}

bool InputManager::IsMouseButtonDown(int button) const
{
	return ((m_OldMouseState & SDL_BUTTON(button)) && (m_CurrMouseState & SDL_BUTTON(button)));
}

bool InputManager::IsMouseButtonReleased(int button) const
{
	return ((m_OldMouseState & SDL_BUTTON(button)) && !(m_CurrMouseState & SDL_BUTTON(button)));
}
