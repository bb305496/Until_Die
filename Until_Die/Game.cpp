#include "stdafx.h"
#include "Game.h"

void Game::initWindow()
{
	this->window.create(sf::VideoMode(1200,600), "Until Die", sf::Style::Default);
	this->window.setFramerateLimit(60);
}

void Game::initTileSheet()
{
	if (!this->tileSheet1.loadFromFile("Textures/Sprites/Main/Kenshin.png"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD THE TILE TEXTURE" << "\n";
	}
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initTileMap()
{
	this->tileMap = new TileMap(20, 20, &this->tileSheet1, 50);
	for (int i = 0; i < 5; i++)
	{
		for (int k = 0; k < 5; k++)
		{
			this->tileMap->addTile(i, k);
		}
	}

}


Game::Game()
{
	this->initWindow();
	this->initTileSheet();
	this->initTileMap();
	this->initPlayer();
}

Game::~Game()
{
	delete this->player;
	delete this->tileMap;
}

void Game::updatePlayer()
{
	this->player->update();
}


void Game::updateCollision()
{
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y)
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			this->window.getSize().y - this->player->getGlobalBounds().height
			);
		this->player->setCanJump();
	}

}

void Game::updateTileMap()
{
	this->tileMap->update();
}

const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}

void Game::update()
{
	while (this->window.pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
			this->window.close();
		else if (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Escape)
			this->window.close();

		if (this->event.type == sf::Event::KeyReleased &&
			(this->event.key.code == sf::Keyboard::A ||
				this->event.key.code == sf::Keyboard::D ||
				this->event.key.code == sf::Keyboard::W ||
				this->event.key.code == sf::Keyboard::S ||
				this->event.key.code == sf::Keyboard::Space))
		{
			this->player->resetAnimationTimer();
		}
	}

	this->updatePlayer();

	this->updateCollision();

	this->updateTileMap();

}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::renderTileMap()
{
	this->tileMap->render(this->window);
}


void Game::render()
{
	this->window.clear();

	//render game
	this->renderTileMap();
	this->renderPlayer();

	this->window.display();
}
