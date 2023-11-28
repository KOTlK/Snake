#include "Game.h"

using namespace sf;

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
    _replayButtonTexture->loadFromFile("resources/replay.png");
    _replayButtonTexture->setSmooth(true);
}

void Game::createField(const int& width, const int& height)
{
    _fieldSize = Vector2i(width, height);
    View view(Vector2f(width * TEXTURE_RESOLUTION / 2 - 16, height * TEXTURE_RESOLUTION / 2 - 16), Vector2f(width * TEXTURE_RESOLUTION, height * TEXTURE_RESOLUTION));
    _window->setView(view);

    _stateMachine = new StateMachine(
        new PlayingState(
            _field = new Field(
                width,
                height,
                CellConfig{
                    TEXTURE_RESOLUTION,
                    TEXTURE_RESOLUTION,
                    _tileTexture,
                    Color::White,
                    TEXTURE_RESOLUTION,
                    TEXTURE_RESOLUTION
                },
                { 0, 0 }
            ),
            _snake = new Snake(
                Vector2i(0, 0),
                _snakeHeadTexture,
                _snakeBodyTexture,
                _snakeTailTexture,
                _snakeBodyAngleTexture),
            new AppleFactory(
                _appleTexture,
                Vector2f(32, 32)
            ),
            3
        ),
        new GameOverState(
            _replayButtonTexture,
            _window),
        _window
    );

    _field->put(0, 0, _snake);
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

            if(event.type == Event::KeyReleased)
            {
	            if(event.key.scancode == Keyboard::Scancode::Space)
	            {
                    _field->debugContent();
	            }
            }
        }


        _window->clear();
        _stateMachine->execute();

        if(_stateMachine->gameRestarted())
        {
            restart();
        }
        _window->display();
    }
}

void Game::restart()
{
    delete _field;
    delete _snake;
    createField(_fieldSize.x, _fieldSize.y);
}

void Game::exit()
{
    deleteField();
    _window->close();
}
