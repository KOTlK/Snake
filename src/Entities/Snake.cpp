#include "Snake.h"
#include <cmath>

using namespace sf;


SnakePart::SnakePart(const int& x, const int& y, SnakePart* next, SnakePart* previous) :
	next(next),
	previous(previous),
	vertices(new Vertex[6]),
	movedFrom(x, y),
	direction(1, 0),
	x(x),
	y(y)
{
	createVertices();
}

SnakePart::SnakePart(const Vector2i& position, const Vector2i& previousPosition, SnakePart* next,
	SnakePart* previous) :
	next(next),
	previous(previous),
	vertices(new Vertex[6]),
	movedFrom(previousPosition),
	direction(previousPosition - position),
	x(position.x),
	y(position.y)
{
	setRotation(atan2f(direction.y, direction.x) * 57.2958F);
	createVertices();
}

SnakePart::~SnakePart()
{
	delete[] vertices;
}

void SnakePart::replace(const int& argX, const int& argY)
{
	if(next != nullptr)
	{
		next->replace(x, y);
	}

	movedFrom = Vector2i(x, y);
	direction = Vector2i(argX - x, argY - y);
	x = argX;
	y = argY;
	setPosition(x * 32, y * 32);
}

void SnakePart::recalculateRotation()
{
	bool isAngled = false;
	Vector2i directionToNext;

	if(next != nullptr && previous != nullptr)
	{
		const auto absDirectionToPrevious = Vector2i(abs(previous->x - x), abs(previous->y - y));
		const auto absDirectionToHead = Vector2i(abs(x - next->x), abs(y - next->y));
		const auto directionSum = absDirectionToPrevious + absDirectionToHead;

		if (directionSum == Vector2i(1, 1))
		{
			isAngled = true;
			directionToNext = Vector2i(next->x - x, next->y - y);
		}
	}

	if(previous == nullptr)
	{
		direction = Vector2i(x, y) - movedFrom;
	}else
	{
		direction = Vector2i(previous->x, previous->y) - Vector2i(x, y);
	}

	if(direction == Vector2i(1, 0))
	{
		if(isAngled)
		{
			if(directionToNext == Vector2i(0, 1))
			{
				setRotation(0);
			}else if(directionToNext == Vector2i(0, -1))
			{
				setRotation(270);
			}
		}else
		{
			setRotation(0);
		}
	}else if(direction == Vector2i(0, 1))
	{
		if(isAngled)
		{
			if(directionToNext == Vector2i(-1, 0))
			{
				setRotation(90);
			}else
			{
				setRotation(0);
			}
		}else
		{
			setRotation(90);
		}
	}else if(direction == Vector2i(-1, 0))
	{
		if (isAngled)
		{
			if(directionToNext == Vector2i(0, 1))
			{
				setRotation(90);
			}else
			{
				setRotation(180);
			}
		}
		else
		{
			setRotation(180);
		}
	}else if(direction == Vector2i(0, -1))
	{
		if (isAngled)
		{
			if(directionToNext == Vector2i(-1, 0))
			{
				setRotation(180);
			}else
			{
				setRotation(270);
			}
		}
		else
		{
			setRotation(270);
		}
	}

	if(next != nullptr)
	{
		next->recalculateRotation();
	}
}

void SnakePart::createVertices()
{
	setPosition(x * 32, y * 32);
	setOrigin(x * 32, y * 32);

	const Vector2f position(x * 32, y * 32);

	const Vector2f halfSize(16, 16);

	const Vector2f first = position + Vector2f(-halfSize.x, halfSize.y);
	const Vector2f second = position + Vector2f(halfSize.x, halfSize.y);
	const Vector2f third = position + Vector2f(halfSize.x, -halfSize.y);
	const Vector2f fourth = position + Vector2f(-halfSize.x, -halfSize.y);

	vertices[0] = Vertex(first, Color::White, Vector2f(0, 32));
	vertices[1] = Vertex(second, Color::White, Vector2f(32, 32));
	vertices[2] = Vertex(third, Color::White, Vector2f(32, 0));
	vertices[3] = Vertex(first, Color::White, Vector2f(0, 32));
	vertices[4] = Vertex(third, Color::White, Vector2f(32, 0));
	vertices[5] = Vertex(fourth, Color::White, Vector2f(0, 0));
}

Snake::Snake(const Vector2i& position, Texture* headTexture, Texture* bodyTexture, Texture* tailTexture, Texture* bodyAngleTexture) :
	Entity(headTexture, new Vertex[1], 1),
	_headTexture(headTexture),
	_bodyTexture(bodyTexture),
	_tailTexture(tailTexture),
	_bodyAngleTexture(bodyAngleTexture),
	_head(new SnakePart(position.x, position.y))
{
}

Snake::~Snake()
{
	SnakePart* current = _head;
	SnakePart* next = current->next;

	while (current->next != nullptr)
	{
		next = current->next;
		delete current;
		current = next;
	}

	delete next;
}

void Snake::move(const int& x, const int& y, Field& field)
{
	const Vector2i targetPosition = Vector2i(_head->x, _head->y) + Vector2i(x, y);

	if(field.occupied(targetPosition.x ,targetPosition.y))
	{
		const auto content = field.content(targetPosition.x, targetPosition.y);

		switch (content)
		{
		case CellContent::Apple:
			feed();
			field.clear(targetPosition.x, targetPosition.y);
			break;
		case CellContent::Wall:
			return;
		case CellContent::Snake:
			return;
		default:
			break;
		}
		
		//TODO: eat apple or die
	}

	auto head = _head;

	field.clear(head->x, head->y);
	while(head->next != nullptr)
	{
		head = head->next;
		field.clear(head->x, head->y);
	}

	_head->replace(targetPosition.x, targetPosition.y);
	_head->recalculateRotation();

	head = _head;

	field.put(head->x, head->y, this);

	while(head->next != nullptr)
	{
		head = head->next;
		field.put(head->x, head->y, this);
	}
}

void Snake::feed()
{
	auto head = _head;
	while(head->next != nullptr)
	{
		head = head->next;
	}

	const auto position = Vector2i(head->x, head->y) - head->direction;

	head->next = new SnakePart(Vector2i(position.x, position.y), Vector2i(head->x, head->y), nullptr, head);

	_head->recalculateRotation();
}

void Snake::draw(RenderTarget& target, RenderStates states) const
{
	auto head = _head;
	RenderStates statesCopy(states);
	statesCopy.transform *= head->getTransform();
	statesCopy.texture = _headTexture;
	target.draw(head->vertices, 6, Triangles, statesCopy);

	while(head->next != nullptr)
	{
		statesCopy = RenderStates(states);
		head = head->next;
		statesCopy.transform *= head->getTransform();

		

		if(head->next == nullptr)
		{
			statesCopy.texture = _tailTexture;
		}else
		{
			auto directionToPrevious = Vector2i(abs(head->previous->x - head->x), abs(head->previous->y - head->y));
			auto directionToHead = Vector2i(abs(head->x - head->next->x), abs(head->y - head->next->y));
			auto directionSum = directionToPrevious + directionToHead;

			if (directionSum == Vector2i(1, 1))
			{
				statesCopy.texture = _bodyAngleTexture;
			} else
			{
				statesCopy.texture = _bodyTexture;
			}
		}

		target.draw(head->vertices, 6, Triangles, statesCopy);
	}
}
