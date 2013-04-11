#ifndef __RGL_INPUT_MANAGER_H__
#define __RGL_INPUT_MANAGER_H__

#include "../Common.h"

namespace RGL {

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

        ReturnValue Initialize();
        ReturnValue Finish();

		ReturnValue Update();

		bool KeyPress(int keyCode);

		bool MustQuit();

	private:
        bool _isInitialized;

		bool _mustQuit;

		Uint8 *_keys; 

	};

}

#endif
