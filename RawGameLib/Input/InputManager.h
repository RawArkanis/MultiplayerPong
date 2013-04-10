#ifndef __RGL_INPUT_MANAGER_H__
#define __RGL_INPUT_MANAGER_H__

#include "../Common.h"

namespace RGL {

	class InputManager // TODO permitir apenas uma instancia
	{
	public:
		InputManager();
		~InputManager();

		void Update();

		bool KeyPress(int keyCode);

		bool MustQuit();

	private:
		bool _mustQuit;

		Uint8 *_keys; 

	};

}

#endif
