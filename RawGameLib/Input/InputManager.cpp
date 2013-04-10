#include "InputManager.h"

namespace RGL {

	InputManager::InputManager()
		: _mustQuit(false),
		_keys(SDL_GetKeyboardState(NULL))
	{
	}

	InputManager::~InputManager()
	{
	}

	void InputManager::Update()
	{
		SDL_Event e;

		while(SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				_mustQuit = true;
		}
	}

	bool InputManager::KeyPress(int keyCode)
	{
		return _keys[keyCode] == 1;
	}

	bool InputManager::MustQuit()
	{
		return _mustQuit;
	}

}
