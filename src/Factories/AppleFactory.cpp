#include "AppleFactory.h"

using namespace sf;

AppleFactory::AppleFactory(sf::Texture* texture, const sf::Vector2f& size) :
	_appleTexture(texture),
	_size(size)
{
}

AppleFactory::~AppleFactory()
{
	for (const auto apple : _createdApples)
	{
		delete apple;
	}

	_createdApples.clear();
}

Apple* AppleFactory::create(const sf::Vector2f& position)
{
	const auto apple = new Apple(_appleTexture, position, _size);
	_createdApples.insert(apple);
	return apple;
}

void AppleFactory::destroy(Apple* apple)
{
	if(_createdApples.count(apple) > 0)
	{
		_createdApples.erase(apple);
	}

	delete apple;
}

