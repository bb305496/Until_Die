#pragma once

#include "Tile.h"
#include "Player.h"

class TileMap
{
private:
	std::vector<std::vector<Tile*>> tiles;
	sf::Texture* tileSheet;
	unsigned tileSize;
	sf::FloatRect tileBounds;

	sf::FloatRect playerBounds;

public:
	TileMap();
	TileMap(unsigned width, unsigned height, sf::Texture* tile_sheet, unsigned tile_size);
	~TileMap();

	inline const unsigned& getTileSize() const { return this->tileSize; };

	void checkPlayerCollision(Player* player);

	void addTile(unsigned x, unsigned y);
	void removeTile(unsigned x, unsigned y);

	void update();
	void render(sf::RenderTarget& target);
};

