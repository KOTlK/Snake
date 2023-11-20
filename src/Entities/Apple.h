#pragma once

#include "Entity.h"

class Apple : public Entity
{
public:
	explicit Apple(sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size);
};