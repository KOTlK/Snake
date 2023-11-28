#include "Apple.h"

using namespace sf;

Apple::Apple(Texture* texture, const Vector2f& position, const sf::Vector2f& size) :
	Entity(texture, new Vertex[6], 6),
	_eaten(false)
{
	const Vector2f actualPosition = position * 32.0F;
	setPosition(actualPosition);
	setOrigin(actualPosition.x, actualPosition.y);

	const Vector2f halfSize = size * 0.5f;

	const Vector2f first = actualPosition + Vector2f(-halfSize.x, halfSize.y);
	const Vector2f second = actualPosition + Vector2f(halfSize.x, halfSize.y);
	const Vector2f third = actualPosition + Vector2f(halfSize.x, -halfSize.y);
	const Vector2f fourth = actualPosition + Vector2f(-halfSize.x, -halfSize.y);

	_vertices[0] = Vertex(first, Color::White, Vector2f(0, 32));
	_vertices[1] = Vertex(second, Color::White, Vector2f(32, 32));
	_vertices[2] = Vertex(third, Color::White, Vector2f(32, 0));
	_vertices[3] = Vertex(first, Color::White, Vector2f(0, 32));
	_vertices[4] = Vertex(third, Color::White, Vector2f(32, 0));
	_vertices[5] = Vertex(fourth, Color::White, Vector2f(0, 0));
}

bool Apple::eaten() const
{
	return _eaten;
}

void Apple::eat()
{
	_eaten = true;
}
