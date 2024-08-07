#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "TileMap.h"

class Game
{
private:
	sf::RenderWindow window;
	float windowLeft;
	sf::Event event;
	sf::Texture grassTile;
	sf::Texture grass;

	sf::Texture bgTexture;
	sf::Sprite bgSprite;

	sf::Clock clock;
	float deltaTime;

	Player* player;
	sf::FloatRect playerBounds;

	TileMap* tileMap;
	TileMap* grassMap;



	void initWindow();
	void initTileSheet();
	void initPlayer();
	void initTileMap();
	void initJumpingTile();
	void initBg();

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
	void renderGrass();
	void render();
};

#endif

