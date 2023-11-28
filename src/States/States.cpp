#include "States.h"

#include <iostream>

using namespace sf;

PlayingState::PlayingState(Field* field, Snake* snake, AppleFactory* appleFactory, const size_t& maxApples) :
	_field(field),
	_snake(snake),
	_appleFactory(appleFactory),
	_maxApples(maxApples),
	_gameLost(false),
	_gameWon(false),
	_movementDirection(1, 0)
{
	
}

PlayingState::~PlayingState()
{
	delete _snake;
	delete _field;
	delete _appleFactory;
}

void PlayingState::enter()
{
}

void PlayingState::execute()
{
	
	for (auto i = _apples.rbegin(); i != _apples.rend(); ++i)
	{
		const auto apple = *i;

		if(apple->eaten())
		{
			_apples.erase(apple);
			_appleFactory->destroy(apple);
		}
	}

	while(_apples.size() < _maxApples)
	{
		const auto apple = _appleFactory->create({ 0, 0 });

		_field->put(apple);
		_apples.insert(apple);
	}

	{//movement direction

		if(Keyboard::isKeyPressed(Keyboard::Scancode::A))
		{
			_movementDirection.x = -1;
			_movementDirection.y = 0;
		}

		if(Keyboard::isKeyPressed(Keyboard::Scancode::D))
		{
			_movementDirection.x = 1;
			_movementDirection.y = 0;
		}

		if(Keyboard::isKeyPressed(Keyboard::Scancode::W))
		{
			_movementDirection.y = -1;
			_movementDirection.x = 0;
		}

		if (Keyboard::isKeyPressed(Keyboard::Scancode::S))
		{
			_movementDirection.y = 1;
			_movementDirection.x = 0;
		}
	}

	if(_clock.getElapsedTime().asMilliseconds() >= GameSpeed)
	{
		_clock.restart();

		_snake->move(_movementDirection.x, _movementDirection.y, *_field);
		_gameLost = _snake->dead();
	}
}

void PlayingState::exit()
{
}

bool PlayingState::isGameLost() const
{
	return _gameLost;
}

bool PlayingState::isGameWon() const
{
	return _gameWon;
}

void PlayingState::draw(RenderTarget& target, RenderStates states) const
{
	_field->draw(target, states);
}

FRect::FRect() :
	position({ 0, 0 }),
	size({ 0, 0 })
{
}

FRect::FRect(const sf::Vector2f& position, const sf::Vector2f& size) :
	position(position),
	size(size)
{
}

bool FRect::contains(const sf::Vector2f& point) const
{
	const auto hSize = halfSize();

	if (point.x < position.x - hSize.x)
		return false;

	if (point.y < position.y - hSize.y)
		return false;

	if (point.x > position.x + hSize.x)
		return false;

	if (point.y > position.y + hSize.y)
		return false;

	return true;
}

sf::Vector2f FRect::halfSize() const
{
	return size * 0.5f;
}


GameOverState::GameOverState(
	const Texture* restartButtonTexture,
	RenderWindow* renderWindow) :

	_restartButtonClicked(false),
	_restartButton(Sprite(*restartButtonTexture)),
	_renderWindow(renderWindow),
	_buttonRect()
{
	_restartButton.setOrigin(92 / 2, 79 / 2);
	const auto size = _renderWindow->getSize();
	const auto spriteScreenPosition = Vector2i(size.x / 2, size.y / 2);
	const auto spriteWorldPosition = _renderWindow->mapPixelToCoords(spriteScreenPosition);

	_restartButton.setPosition(spriteWorldPosition);
	_restartButton.setScale(0.5F, 0.5F);
	_buttonRect = FRect(_restartButton.getPosition(), { 92 / 2, 79 / 2 });
}

GameOverState::~GameOverState() = default;


void GameOverState::enter()
{
}

void GameOverState::execute()
{
	const auto rect = _restartButton.getTextureRect();
	const auto mousePosition = _renderWindow->mapPixelToCoords(Mouse::getPosition());

	if(Mouse::isButtonPressed(Mouse::Left))
	{
		std::cout << "Game restarted" << std::endl;
		std::cout << mousePosition.x << ", " << mousePosition.y << "	" << _restartButton.getPosition().x << ", " << _restartButton.getPosition().y << std::endl;
		if (_buttonRect.contains(mousePosition))
		{
			std::cout << "Game restarted 2" << std::endl;
			_restartButtonClicked = true;
		}
	}
}

void GameOverState::exit()
{
}

bool GameOverState::restarted() const
{
	return _restartButtonClicked;
}

void GameOverState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_restartButton);
}

