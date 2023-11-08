#pragma once

#include "SFML/Graphics.hpp"

struct CellConfig
{
	size_t width;
	size_t height;
	sf::Texture* texture;
	sf::Color color;
	size_t textureOffsetX;
	size_t textureOffsetY;
};

class Field : public sf::Transformable, public sf::Drawable
{
private:
	CellConfig _cellConfig;
	sf::Vertex* _vertices;
	sf::VertexBuffer _vertexBuffer;
public:
	Field(const size_t& width, const size_t& height, const CellConfig& cellConfig, const sf::Vector2f& position);
	~Field() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};