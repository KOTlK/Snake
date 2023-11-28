#pragma once

#include "Entity.h"
#include "../Field/Field.h"

class Field;

struct SnakePart final : public sf::Transformable
{
	SnakePart* next;
	SnakePart* previous;
	sf::Vertex* vertices;
	sf::Vector2i movedFrom;
	sf::Vector2i direction;
	int x;
	int y;

	SnakePart(const int& x, const int& y, SnakePart* next = nullptr, SnakePart* previous = nullptr);
	SnakePart(const sf::Vector2i& position, const sf::Vector2i& previousPosition, SnakePart* next = nullptr, SnakePart* previous = nullptr);
	~SnakePart() override;
	void replace(const int& argX, const int& argY);
	void recalculateRotation();

private:
	void createVertices();
};

class Snake : public Entity
{
private:
	sf::Texture* _headTexture;
	sf::Texture* _bodyTexture;
	sf::Texture* _tailTexture;
	sf::Texture* _bodyAngleTexture;
	SnakePart* _head;
	bool _dead;
public:
	Snake(const sf::Vector2i& position, sf::Texture* headTexture, sf::Texture* bodyTexture, sf::Texture* tailTexture, sf::Texture* bodyAngleTexture);
	~Snake() override;
	void move(const int& x, const int& y, Field& field);
	void feed();
	bool dead();
	void putAt(const int& x, const int& y);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
