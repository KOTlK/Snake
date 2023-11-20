#include "Game.h"
#include <random>

using namespace sf;

int randomInt(const int& start, const int& end)
{
    std::random_device device;
    std::mt19937 generator(device());
    auto distribution = std::uniform_int_distribution<std::mt19937::result_type>(start, end);

    return distribution(generator);
}

void Game::createEnvironment()
{
    _window = new RenderWindow({ 1280u, 720u }, "Snake");
    _window->setFramerateLimit(75);
}

void Game::loadResources()
{
    _snakeHeadTexture->loadFromFile("resources/snakehead.png");
    _snakeBodyTexture->loadFromFile("resources/snakebody.png");
    _snakeBodyAngleTexture->loadFromFile("resources/snakebodyangle.png");
    _snakeTailTexture->loadFromFile("resources/snaketail.png");
    _appleTexture->loadFromFile("resources/apple.png");
    _tileTexture->loadFromFile("resources/tile.png");
}

void Game::createField(const int& width, const int& height)
{
    _field = new Field(
        width,
        height,
        CellConfig{
            TEXTURE_RESOLUTION,
            TEXTURE_RESOLUTION,
            _tileTexture,
            Color::White,
            TEXTURE_RESOLUTION,
            TEXTURE_RESOLUTION },
        { 0, 0 });

    View view(Vector2f(width * TEXTURE_RESOLUTION / 2 - 16, height * TEXTURE_RESOLUTION / 2 - 16), Vector2f(width * TEXTURE_RESOLUTION, height * TEXTURE_RESOLUTION));
    _window->setView(view);

    const Vector2i snakePosition(randomInt(0, width - 1), randomInt(0, height - 1));

    _snake = new Snake(snakePosition, _snakeHeadTexture, _snakeBodyTexture, _snakeTailTexture, _snakeBodyAngleTexture);

    _field->put(snakePosition.x, snakePosition.y, _snake);

    const Vector2f applePosition(randomInt(0, width - 1), randomInt(0, height - 1));
    auto apple = new Apple(_appleTexture, applePosition, { 32, 32 });
    _field->put(applePosition.x, applePosition.y, apple);
}

void Game::deleteField()
{
    delete _field;
}


void Game::execute()
{
    while (_window->isOpen())
    {
        for (auto event = Event{}; _window->pollEvent(event);)
        {
            if (event.type == Event::Closed)
            {
                _window->close();
            }

            if (event.type == Event::KeyPressed)
            {
                switch (event.key.scancode)
                {
                case Keyboard::Scancode::D:
                    _snake->move(1, 0, *_field);
                    break;
                case Keyboard::Scancode::A:
                    _snake->move(-1, 0, *_field);
                    break;
                case Keyboard::Scancode::W:
                    _snake->move(0, -1, *_field);
                    break;
                case Keyboard::Scancode::S:
                    _snake->move(0, 1, *_field);
                    break;
                case Keyboard::Scancode::LControl:
                    _snake->feed();
                    break;
                default:
                    break;
                }
            }

        }

        _window->clear();
        _window->draw(*_field);
        _window->display();
    }
}

void Game::exit()
{
    deleteField();
    _window->close();
}
