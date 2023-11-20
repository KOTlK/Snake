#include "Entity.h"

using namespace sf;

Entity::Entity(Texture* texture, sf::Vertex* vertices, const size_t& verticesCount) : _texture(texture), _vertices(vertices), _verticesCount(verticesCount)
{
}

Entity::~Entity()
{
	delete[] _vertices;
}

void Entity::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = _texture;
	
	target.draw(_vertices, _verticesCount, Triangles, states);
}
