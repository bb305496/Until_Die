#pragma once

#include "Tile.h"

class TileMap
{
private:
	std::vector<std::vector<Tile*>> tiles;
	sf::Texture* tileSheet;
	unsigned tileSize;

public:
	TileMap();
	TileMap(unsigned width, unsigned height, sf::Texture* tile_sheet, unsigned tile_size);
	~TileMap();

	inline const unsigned& getTileSize() const { return this->tileSize; };

	void addTile(unsigned x, unsigned y);
	void removeTile(unsigned x, unsigned y);

	void update();
	void render(sf::RenderTarget& target);
};

