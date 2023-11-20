#pragma once

#include "SFML/Graphics.hpp"
#include "Field/Field.h"

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
public:
	void createEnvironment();
	void loadResources();
	void createField(const int& width, const int& height);
	void deleteField();
	void execute();
	void exit();
};

int randomInt(const int& start, const int& end);