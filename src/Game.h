#pragma once

#include "SFML/Graphics.hpp"
#include "Field/Field.h"
#include "States/StateMachine.h"

constexpr int TEXTURE_RESOLUTION = 32;

class Game
{
private:
	sf::RenderWindow* _window = nullptr;
	Field* _field = nullptr;
	Snake* _snake = nullptr;
	sf::Texture* _snakeHeadTexture = new sf::Texture();
	sf::Texture* _snakeBodyTexture = new sf::Texture();
	sf::Texture* _snakeBodyAngleTexture = new sf::Texture();
	sf::Texture* _snakeTailTexture = new sf::Texture();
	sf::Texture* _appleTexture = new sf::Texture();
	sf::Texture* _tileTexture = new sf::Texture();
	sf::Texture* _replayButtonTexture = new sf::Texture();
	StateMachine* _stateMachine;
	sf::Vector2i _fieldSize;
public:
	void createEnvironment();
	void loadResources();
	void createField(const int& width, const int& height);
	void deleteField();
	void execute();
	void restart();
	void exit();
};