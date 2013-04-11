#include "Entity.h"

namespace RGL {

	Entity::Entity(std::weak_ptr<RenderManager> render, const SDL_Rect &rect)
		: _render(render),
		_rect(rect)
	{
	}


	Entity::~Entity()
	{
	}

	SDL_Rect Entity::Rect() const
	{
		return _rect;
	}
	
	void Entity::Rect(const SDL_Rect &rect)
	{
		_rect = rect;
	}

}
