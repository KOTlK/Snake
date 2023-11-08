#include "Field.h"

using namespace sf;

Field::Field(const size_t& width, const size_t& height, const CellConfig& cellConfig, const sf::Vector2f& position) : _cellConfig(cellConfig), _vertexBuffer(Triangles, VertexBuffer::Static)
{
	_vertexBuffer.create(width * height * 6);
	_vertices = new Vertex[width * height * 6];
	size_t verticesCount = 0;
	const Vector2f cellSize(cellConfig.width, cellConfig.height);

	for(size_t y = 0; y < height; ++y)
	{
		for(size_t x = 0; x < width; ++x)
		{
			auto pos = position + Vector2f(x * cellConfig.width, y * cellConfig.height);

			const Vector2f halfSize = cellSize * 0.5f;

			const Vector2f first = pos + Vector2f(-halfSize.x, halfSize.y);
			const Vector2f second = pos + Vector2f(halfSize.x, halfSize.y);
			const Vector2f third = pos + Vector2f(halfSize.x, -halfSize.y);
			const Vector2f fourth = pos + Vector2f(-halfSize.x, -halfSize.y);

			_vertices[verticesCount + 0] = Vertex(first, cellConfig.color, Vector2f(0, cellConfig.textureOffsetY));
			_vertices[verticesCount + 1] = Vertex(second, cellConfig.color, Vector2f(cellConfig.textureOffsetX, cellConfig.textureOffsetY));
			_vertices[verticesCount + 2] = Vertex(third, cellConfig.color, Vector2f(cellConfig.textureOffsetX, 0));
			_vertices[verticesCount + 3] = Vertex(first, cellConfig.color, Vector2f(0, cellConfig.textureOffsetY));
			_vertices[verticesCount + 4] = Vertex(third, cellConfig.color, Vector2f(cellConfig.textureOffsetX, 0));
			_vertices[verticesCount + 5] = Vertex(fourth, cellConfig.color, Vector2f(0, 0));
			verticesCount += 6;
		}
	}

	_vertexBuffer.update(_vertices);
}

Field::~Field()
{
	delete[] _vertices;
}

void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = _cellConfig.texture;
	target.draw(_vertexBuffer, states);
}
