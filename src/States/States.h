#pragma once

#include <set>
#include "State.h"
#include "../Field/Field.h"
#include "../Entities/Snake.h"
#include "../Entities/Apple.h"
#include "../Factories/AppleFactory.h"

class PlayingState final : public State
{
private:
	Field* _field;
	Snake* _snake;
	AppleFactory* _appleFactory;
	std::set<Apple*> _apples;
	size_t _maxApples;
	bool _gameLost;
	bool _gameWon;
	sf::Vector2i _movementDirection;
	sf::Clock _clock;
	constexpr static int GameSpeed = 250;
public:
	PlayingState() = default;
	PlayingState(Field* field, Snake* snake, AppleFactory* appleFactory, const size_t& maxApples);
	~PlayingState() override;

	PlayingState(const PlayingState& other) = delete;
	PlayingState(PlayingState&& other) noexcept = delete;

	void enter() override;
	void execute() override;
	void exit() override;
	bool isGameLost() const;
	bool isGameWon() const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

struct FRect
{
	sf::Vector2f position;
	sf::Vector2f size;
	FRect();
	explicit FRect(const sf::Vector2f& position, const sf::Vector2f& size);
	bool contains(const sf::Vector2f& point) const;
	sf::Vector2f halfSize() const;
};

class GameOverState final : public State
{
private:
	bool _restartButtonClicked;
	sf::Sprite _restartButton;
	sf::RenderWindow* _renderWindow;
	FRect _buttonRect;
public:
	explicit GameOverState(const sf::Texture* restartButtonTexture, sf::RenderWindow* renderWindow);
	~GameOverState() override;
	void enter() override;
	void execute() override;
	void exit() override;
	bool restarted() const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
