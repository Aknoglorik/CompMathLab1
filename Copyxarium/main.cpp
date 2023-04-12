#include "App.h"

int main()
{
	App game(100, 100, "CopyXarium");


    while (game.isOpen())
    {
        game.update();
        game.render();
    }

	return 0;
}