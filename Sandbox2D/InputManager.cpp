#include "../stdafx.h"

InputManager::InputManager()
{
	_currKeyboardState = SDL_GetKeyboardState(&_keyboardStateLength);
	_oldKeyboardState = new Uint8[_keyboardStateLength];

	_currMouseState = SDL_GetMouseState(&_mouseLocation.x, &_mouseLocation.y);
	_oldMouseState = _currMouseState;

	loadKeymapFromConfig();
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

SDL_Scancode InputManager::getKeymapScancode(const std::string key)
{
	if (_keymap.find(key) == _keymap.end()) return SDL_Scancode();
	return _keymap[key];
}

void InputManager::writeScancodeToKeymap(const std::string key, const SDL_Scancode scancode)
{
	_keymap[key] = scancode;
}

void InputManager::writeKeymapToConfig()
{
	auto ini = new IniFile();

	ini->createSection("controls");
	for (const auto &pair : _keymap)
	{
		ini->setValue("controls", { pair.first, std::to_string(pair.second) });
	}

	ini->write("Config/controls.ini");
	delete ini;
}

void InputManager::loadKeymapFromConfig()
{
	auto controlsIni = new IniFile("Config/controls.ini");
	controlsIni->parse();
	for (const auto &section : controlsIni->getSection("controls"))
	{
		_keymap[section.first] = SDL_Scancode(std::stoi(section.second));
	}

	delete controlsIni;

	if (_keymap.empty()) LogWarning("Inputmanager's keymap is empty, ignore if Config/controls.ini is also empty.");
}
