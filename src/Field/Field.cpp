#include "Field.h"

#include <iostream>

#include "../Random.h"

using namespace sf;


Field::Field(const size_t& width, const size_t& height, const CellConfig& cellConfig, const sf::Vector2f& position) :
	_width(width),
	_height(height),
	_cellConfig(cellConfig),
	_vertexBuffer(Triangles, VertexBuffer::Static),
	_snakes(),
	_apples()
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

	for(size_t y = 0; y < height; ++y)
	{
		for(size_t x = 0; x < width; ++x)
		{
			_freeCells.insert(std::pair(x, y));
		}
	}
}

Field::~Field()
{
	delete[] _vertices;
}

bool Field::occupied(const int& x, const int& y) const
{
	if(x < 0 ||
		x >= _width ||
		y < 0 ||
		y >= _height)
	{
		return true;
	}

	const std::pair position(x, y);

	return _freeCells.count(position) == 0;
}

void Field::put(const int& x, const int& y, Snake* snake)
{
	const auto pos = std::make_pair(x, y);

	_snakes[pos] = snake;
	_freeCells.erase(pos);
}

void Field::put(const int& x, const int& y, Apple* apple)
{
	const auto pos = std::make_pair(x, y);
	_apples[pos] = apple;
	_freeCells.erase(pos);
	apple->setPosition(Vector2f(x * _cellConfig.width, y * _cellConfig.height));
}

void Field::put(Apple* apple)
{
	const auto size = _freeCells.size();

	if (size == 0)
	{
		apple->eat();
		return;
	}


	const auto randomIndex = randomInt(0, size - 1);
	int index = 0;

	for (auto pos : _freeCells)
	{
		if(index == randomIndex)
		{
			_apples[pos] = apple;
			apple->setPosition(Vector2f(pos.first * _cellConfig.width, pos.second * _cellConfig.height));
			_freeCells.erase(pos);
			break;
		}

		index++;
	}
}

void Field::put(Snake* snake)
{
	const auto size = _freeCells.size();

	if (size == 0)
	{
		return;
	}


	const auto randomIndex = randomInt(0, size - 1);
	int index = 0;

	for (auto pos : _freeCells)
	{
		if (index == randomIndex)
		{
			_snakes[pos] = snake;
			snake->putAt(pos.first, pos.second);
			_freeCells.erase(pos);
			break;
		}

		index++;
	}
}

Apple* Field::getApple(const int& x, const int& y)
{
	if(_apples.count(std::pair(x, y)) > 0)
	{
		return _apples[std::pair(x, y)];
	}

	return nullptr;
}

void Field::clear(const int& x, const int& y)
{
	const std::pair position(x, y);

	if(_snakes.count(position) > 0)
	{
		_snakes.erase(position);
		_freeCells.insert(position);
	}

	if(_apples.count(position) > 0)
	{
		_apples.erase(position);
		_freeCells.insert(position);
	}
}

CellContent Field::content(const int& x, const int& y) const
{
	if(_snakes.count(std::pair(x, y)) > 0)
	{
		return CellContent::Snake;
	}

	if(_apples.count(std::pair(x, y)) > 0)
	{
		return CellContent::Apple;
	}

	if(x < 0 ||
		x >= _width ||
		y < 0 ||
		y >= _height)
	{
		return CellContent::Wall;
	}

	return CellContent::Empty;
}

void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = _cellConfig.texture;
	target.draw(_vertexBuffer, states);

	for(const auto [position, apple] : _apples)
	{
		target.draw(*apple);
	}

	for(const auto [position, snake] : _snakes)
	{
		target.draw(*snake);
	}
}

void Field::debugContent()
{
	for (size_t y = 0; y < _height; ++y)
	{
		for (size_t x = 0; x < _width; ++x)
		{
			std::cout << static_cast<int>(content(x, y)) << ", ";
		}

		std::cout << std::endl;
	}

	for(const auto position : _freeCells)
	{
		std::cout << position.first << ", " << position.second << std::endl;
	}
}
