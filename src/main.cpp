#include "main.h"

#include "Field/Field.h"

using namespace std;
using namespace sf;

int main()
{
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

    while (window.isOpen())
    {
        for (auto event = Event{}; window.pollEvent(event);)
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(field);
        window.display();
    }

	return 0;
}
