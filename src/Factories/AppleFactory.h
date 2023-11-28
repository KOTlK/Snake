#pragma once

#include "../Entities/Apple.h"
#include "SFML/Graphics.hpp"
#include <set>

class AppleFactory
{
private:
	sf::Texture* _appleTexture;
	sf::Vector2f _size;
	std::set<Apple*> _createdApples;
public:
	AppleFactory(sf::Texture* texture, const sf::Vector2f& size);
	~AppleFactory();
	Apple* create(const sf::Vector2f& position);
	void destroy(Apple* apple);
};