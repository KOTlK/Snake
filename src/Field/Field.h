#pragma once

#include <set>
#include <unordered_map>
#include "../Entities/Apple.h"
#include "SFML/Graphics.hpp"
#include "../Entities/Snake.h"

class Snake;

struct CellConfig
{
	size_t width;
	size_t height;
	sf::Texture* texture;
	sf::Color color;
	float textureOffsetX;
	float textureOffsetY;
};

namespace std
{
	struct hash_pair
	{
		template <class T1, class T2>
		size_t operator()(const pair<T1, T2>& p) const
		{
			auto hash1 = hash<T1>{}(p.first);
			auto hash2 = hash<T2>{}(p.second);

			if (hash1 != hash2)
			{
				return hash1 ^ hash2;
			}

			return hash1;
		}
	};
}

enum class CellContent
{
	Snake = 1,
	Apple = 2,
	Empty = 0,
	Wall = 3
};

class Field : public sf::Transformable, public sf::Drawable
{
private:
	size_t _width;
	size_t _height;
	CellConfig _cellConfig;
	sf::Vertex* _vertices;
	sf::VertexBuffer _vertexBuffer;
	std::unordered_map<std::pair<int, int>, Snake*, std::hash_pair> _snakes;
	std::unordered_map<std::pair<int, int>, Apple*, std::hash_pair> _apples;
	std::set<std::pair<int, int>> _freeCells;
public:
	Field(const size_t& width, const size_t& height, const CellConfig& cellConfig, const sf::Vector2f& position);
	~Field() override;
	bool occupied(const int& x, const int& y) const;
	void put(const int& x, const int& y, Snake* snake);
	void put(const int& x, const int& y, Apple* apple);

	/**
	 * \brief put an apple at random position
	 */
	void put(Apple* apple);
	void put(Snake* snake);
	Apple* getApple(const int& x, const int& y);
	void clear(const int& x, const int& y);
	CellContent content(const int& x, const int& y) const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void debugContent();
};
