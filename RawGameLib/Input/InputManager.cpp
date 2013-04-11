#include "InputManager.h"

namespace RGL {

	InputManager::InputManager()
		: _isInitialized(false),
        _mustQuit(false),
		_keys(nullptr)
	{
	}

	InputManager::~InputManager()
	{
	}

    ReturnValue InputManager::Initialize()
    {
        if (_isInitialized)
            return R_ERR_ALREADY_INITIALIZED;

        _keys = SDL_GetKeyboardState(NULL);

        _isInitialized = true;

        return R_OK;
    }

    ReturnValue InputManager::Finish()
    {
        if (!_isInitialized)
            return R_ERR_NOT_INITIALIZAED;

        _keys = nullptr;
        _mustQuit = false;
        
        _isInitialized = false;

        return R_OK;
    }

	ReturnValue InputManager::Update()
	{
        if (!_isInitialized)
            return R_ERR_NOT_INITIALIZAED;

		SDL_Event e;

		while(SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				_mustQuit = true;
		}

        return R_OK;
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
