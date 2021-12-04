#include <SFML/Graphics.hpp>
#include "Game.h"
int main()
{
	//Call game here
	srand(time(NULL));//resets rand so that it dosen't have the same rand pattern every time
	Game game;
	game.run();
	return 0;
}