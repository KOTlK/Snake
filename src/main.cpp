#include "main.h"

#include "Entities/Apple.h"
#include "Field/Field.h"
#include "Game.h"

using namespace std;
using namespace sf;

int main()
{
	/*
	auto window = RenderWindow({1280u, 720u}, "Snake");
	window.setFramerateLimit(75);
    int width = 16;
    int height = 9;
    Texture cellTexture;
    cellTexture.loadFromFile("resources/tile.png");
    CellConfig cellConfig{ 32, 32, &cellTexture, Color::White, 32, 32 };

    Field field(width, height, cellConfig, Vector2f(0, 0));

    float fieldWidth = width * 32;
    float fieldHeight = height * 32;

    View view(Vector2f(fieldWidth / 2 - 16, fieldHeight / 2 - 16), Vector2f(fieldWidth, fieldHeight));
    window.setView(view);

    Texture appleTexture;
    appleTexture.loadFromFile("resources/apple.png");
    Apple apple(&appleTexture, { 100, 100 }, { 32, 32 });
    Texture snakeHeadTexture;
    snakeHeadTexture.loadFromFile("resources/snakehead.png");
    Texture snakeBodyTexture;
    snakeBodyTexture.loadFromFile("resources/snakebody.png");
    Texture snakeTailTexture;
    snakeTailTexture.loadFromFile("resources/snaketail.png");

    auto snake = new Snake(Vector2i(0,0), &snakeHeadTexture, &snakeBodyTexture, &snakeTailTexture);

    field.put(0, 0, snake);
    field.put(9, 8, &apple);

    while (window.isOpen())
    {
        for (auto event = Event{}; window.pollEvent(event);)
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if(event.type == Event::KeyPressed)
            {
	            switch (event.key.scancode)
	            {
	            case Keyboard::Scancode::D:
                    snake->move(1, 0, field);
                    break;
                case Keyboard::Scancode::A:
                    snake->move(-1, 0, field);
                    break;
                case Keyboard::Scancode::W:
                    snake->move(0, -1, field);
                    break;
                case Keyboard::Scancode::S:
                    snake->move(0, 1, field);
                    break;
	            case Keyboard::Scancode::LControl:
                    snake->feed();
                    break;
	            default:
                    break;
	            }
            }

        }

        window.clear();
        window.draw(field);
        window.display();
    }
    */
    Game game;

    game.createEnvironment();
    game.loadResources();
    game.createField(16, 9);
    game.execute();
    game.exit();

	return 0;
}
