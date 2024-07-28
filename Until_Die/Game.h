#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event event;

	Player* player;

	void initWindow();
	void initPlayer();

public:
	Game();
	~Game();

	
	const sf::RenderWindow& getWindow() const;
	void updatePlayer();
	void updateCollision();
	void update();
	void renderPlayer();
	void render();
};

#endif

