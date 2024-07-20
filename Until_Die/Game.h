#pragma once
#include <SFML/Graphics.hpp>

class Game
{
private:
	sf::RenderWindow mWindow;
	sf::CircleShape mPlayer;


	void processEvents();
	void update();
	void render();

public:
	Game();
	~Game();

	void run();
};

