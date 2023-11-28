#include "main.h"

#include "Field/Field.h"
#include "Game.h"

using namespace std;
using namespace sf;

int main()
{
    Game game;

    game.createEnvironment();
    game.loadResources();
    game.createField(16, 9);
    game.execute();
    game.exit();

	return 0;
}
