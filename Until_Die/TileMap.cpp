#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap()
{
	this->tileSheet = nullptr;
	this->tileSize = 0;
}

TileMap::TileMap(unsigned width, unsigned height, sf::Texture* tile_sheet, unsigned tile_size)
{
	this->tileSheet = tile_sheet;
	this->tileSize = tile_size;

	this->tiles.resize(width);
	for (int i = 0; i < this->tiles.size(); i++)
	{
		this->tiles[i].resize(height, nullptr);
	}
}

TileMap::~TileMap()
{
	for (int i = 0; i < this->tiles.size(); i++)
	{
		for (int k = 0; k < this->tiles[i].size(); k++)
		{
			delete this->tiles[i][k];
			this->tiles[i][k] = nullptr;
		}
	}
}

void TileMap::checkPlayerCollision(Player* player)
{
	this->playerBounds = player->getGlobalBounds(); 

	for (int i = 0; i < this->tiles.size(); i++)
	{
		for (int k = 0; k < this->tiles[i].size(); k++)
		{
			Tile* tile = this->tiles[i][k];

			if (tile != nullptr)
			{
				this->tileBounds = tile->getGlobalBounds();

				if (playerBounds.intersects(tileBounds))
				{

					player->setPosition(player->getPosition().x, tileBounds.top - player->getGlobalBounds().height);
					player->resetVelocityY();
					player->setCanJump();
				}
			}
		}
	}
}

void TileMap::addTile(unsigned x, unsigned y)
{
	if (x < this->tiles.size() && x >= 0)
	{
		if (y < this->tiles[x].size() && y >= 0)
		{
			if (this->tiles[x][y] == nullptr)
			{
				this->tiles[x][y] = new Tile(x,y, this->tileSize, this->tileSheet, sf::IntRect(0, 0, this->tileSize, this->tileSize), false);
			}
		}
	}
}

void TileMap::removeTile(unsigned x, unsigned y)
{
	if (x < this->tiles.size())
	{
		if (y < this->tiles[x].size())
		{
			if (this->tiles[x][y] != nullptr)
			{
				delete this->tiles[x][y];
				this->tiles[x][y] = nullptr;
			}
		}
	}
}

void TileMap::update()
{
	for (int i = 0; i < this->tiles.size(); i++)
	{
		for (int k = 0; k < this->tiles[i].size(); k++)
		{
			if (this->tiles[i][k] != nullptr)
				this->tiles[i][k]->update();
		}
	}
}

void TileMap::render(sf::RenderTarget& target)
{
	for (int i = 0; i < this->tiles.size(); i++)
	{
		for (int k = 0; k < this->tiles[i].size(); k++)
		{
			if (this->tiles[i][k] != nullptr)
				this->tiles[i][k]->render(target);
		}
	}
}
