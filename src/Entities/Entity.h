#pragma once

#include "SFML/Graphics.hpp"

class Entity : public sf::Transformable, public sf::Drawable
{
protected:
	sf::Texture* _texture;
	sf::Vertex* _vertices;
	size_t _verticesCount;
public:
	explicit Entity(sf::Texture* texture, sf::Vertex* vertices, const size_t& verticesCount);
	~Entity() override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};