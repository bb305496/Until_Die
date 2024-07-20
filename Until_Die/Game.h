#ifndef GAME_H
#define GAME_H

#include "stdafx.h"

class Game
{
private:
	sf::RenderWindow window;

	void initWindow();

public:
	Game();
	~Game();
};

#endif

