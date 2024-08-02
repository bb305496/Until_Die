#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "TileMap.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event event;
	sf::Texture tileSheet1;

	Player* player;
	TileMap* tileMap;

	void initWindow();
	void initTileSheet();
	void initPlayer();
	void initTileMap();

public:
	Game();
	~Game();

	
	const sf::RenderWindow& getWindow() const;
	void updatePlayer();
	void updateCollision();
	void updateTileMap();
	void update();

	void renderPlayer();
	void renderTileMap();
	void render();
};

#endif

