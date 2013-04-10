#ifndef __RGL_ENTITY_H__
#define __RGL_ENTITY_H__

#include "../Common.h"

namespace RGL {

	class WindowManager;

	class Entity
	{
	public:
		Entity(std::weak_ptr<WindowManager> window, const SDL_Rect &rect);
		~Entity();
	
		SDL_Rect Rect() const;
		void Rect(const SDL_Rect &rect);

	private:
		std::weak_ptr<WindowManager> _window;

		SDL_Rect _rect;
	};

}

#endif
