#ifndef __RGL_ENTITY_H__
#define __RGL_ENTITY_H__

#include "../Common.h"

namespace RGL {

	class RenderManager;

	class Entity
	{
	public:
		Entity(std::weak_ptr<RenderManager> render, const SDL_Rect &rect);
		~Entity();
	
		SDL_Rect Rect() const;
		void Rect(const SDL_Rect &rect);

		virtual void Update(double delta) = 0;
		virtual void Draw(const SDL_Rect& rect) = 0;

	protected:
		std::weak_ptr<RenderManager> _render;

		SDL_Rect _rect;
	};

}

#endif
