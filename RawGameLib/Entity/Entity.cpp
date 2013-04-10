#include "Entity.h"

namespace RGL {

	Entity::Entity(std::weak_ptr<WindowManager> window, const SDL_Rect &rect)
		: _window(window),
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
