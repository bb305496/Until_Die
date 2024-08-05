#include "stdafx.h"
#include "Game.h"

void Game::initWindow()
{
	this->window.create(sf::VideoMode(1920,1080), "Until Die", sf::Style::Fullscreen);
	this->window.setFramerateLimit(60);
}

void Game::initTileSheet()
{
	if (!this->grassTile.loadFromFile("Textures/Tiles/GrassTile.png"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD THE TILE TEXTURE" << "\n";
	}

	if (!this->grass.loadFromFile("Textures/Tiles/Grass.png"))
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
	this->tileMap = new TileMap(50, 22, &this->grassTile, 50);
	this->grassMap = new TileMap(50, 21, &this->grass, 50);

	//Grass
	for (int i = 0; i < 49;i++)
	{
		this->grassMap->addTile(i, 20);
	}
	//Ground
	for (int i = 0; i < 49 ;i++)
	{
		this->tileMap->addTile(i, 21);
	}
}

void Game::initBg()
{
	if (!this->bgTexture.loadFromFile("Textures/Bg/ForestBg.png"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD FORESTBG TEXTURE " << "\n";
	}

	this->bgSprite.setTexture(this->bgTexture);
}


Game::Game()
{
	this->initWindow();
	this->initBg();
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
	this->player->update(this->deltaTime);
}


void Game::updateCollision()
{	

	this->playerBounds = this->player->getGlobalBounds();
	this->windowLeft = 0.f;

	if (this->playerBounds.left < windowLeft)
	{
		this->player->setPosition(windowLeft, playerBounds.top);
		this->player->resetVelocityX();
	}
	this->tileMap->checkPlayerCollision(this->player);
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
	sf::Time dt = clock.restart();
	deltaTime = dt.asSeconds() * 20.f;

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

void Game::renderGrass()
{
	this->grassMap->render(this->window);
}


void Game::render()
{
	this->window.clear();

	//render game
	this->window.draw(this->bgSprite);
	this->renderTileMap();
	this->renderPlayer();
	this->renderGrass();

	this->window.display();
}
