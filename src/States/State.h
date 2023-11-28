#pragma once

#include "SFML/Graphics.hpp"

class State : public sf::Drawable
{
public:
	State() = default;
	~State() override = default;
	virtual void enter() = 0;
	virtual void execute() = 0;
	virtual void exit() = 0;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
	}
};
