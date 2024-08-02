#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->animState = IDLE;
	this->canJump = true;
	this->castULT = false;
	this->isCastingULT = false;
	this->movingLeft = false;
	this->movingRight = false;
}

void Player::initTexture()
{
	if (!this->texture.loadFromFile("Textures/Sprites/Main/Kenshin.png"))
	{
		std::cout << "ERROR::PLAYER::COULD NOT LOAD THE PLAYER TEXTURE" << "\n";
	}

	if(!this->ultTexture.loadFromFile("Textures/Sprites/Main/ULT.png"))
	{
		std::cout << "ERROR::PLAYER::COULD NOT LOAD THE ULT TEXTURE" << "\n";
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->currentFrame = sf::IntRect(0, 0, 56, 70);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(1.5f, 1.5f);
	/*this->sprite.setOrigin(this->currentFrame.width / 2, this->currentFrame.height);*/
	//this->sprite.setPosition(600.f, 600.f);

	this->ultSprite.setTexture(this->ultTexture);
	this->ultCurrentFrame = sf::IntRect(0, 0, 256, 210);
	this->ultSprite.setTextureRect(this->ultCurrentFrame);
	this->ultSprite.setScale(1.5f, 1.5f);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->velocityMax = 10.f;
	this->velocityMin = 1.f;
	this->acceleration = 0.9f;
	this->drag = 0.90f;
	this->gravity = 2.5f;
	this->velocityMaxY = 45.f;
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();
}

Player::~Player()
{

}

const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch;
}

const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityY()
{
	this->velocity.y = 0;
}

bool Player::getCanJump()
{
	return this->canJump;
}

void Player::setCanJump()
{
	this->canJump = true;
}

void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
	this->velocity.x += dir_x * this->acceleration;
	

	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
}

void Player::jump()
{
	this->velocity.y = -this->velocityMaxY;

}

void Player::updatePhysics()
{
	//Gravity
	this->velocity.y += 1.0f * this->gravity;
	if (std::abs(this->velocity.y) > this->velocityMaxY)
	{
		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}

	this->velocity *= this->drag;

	if (std::abs(this->velocity.x) < this->velocityMin)
	{
		this->velocity.x = 0.f;
	}
	if (std::abs(this->velocity.y) < this->velocityMin)
	{
		this->velocity.y = 0.f;
	}

	this->sprite.move(this->velocity);
}

void Player::updateMovement()
{
	if (this->isCastingULT)
		return;

	this->animState = IDLE;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		this->move(-5.f, 0.f);
		this->animState = MOVING_LEFT;
		this->movingLeft = true;
		this->movingRight = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		this->move(5.f, 0.f);
		this->animState = MOVING_RIGHT;
		this->movingRight = true;
		this->movingLeft = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && this->canJump)
	{
		this->jump();
		this->canJump = false;
	}

}

void Player::updateAttack()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4) && !this->castULT)
	{
		this->animState = ULT;
		this->isCastingULT = true;
	}
}

void Player::updateAnimations()
{
	if (this->animState == IDLE)
	{
		if (this->animationTimer.getElapsedTime().asMilliseconds() >= 140.f || this->getAnimSwitch())
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 56.f;
			if (this->currentFrame.left >= 224.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == MOVING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asMilliseconds() >= 90.f || this->getAnimSwitch())
		{
			this->currentFrame.top = 75.f;
			this->currentFrame.left += 56.f;
			if (this->currentFrame.left >= 224.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(1.5f, 1.5f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animState == MOVING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asMilliseconds() >= 90.f || this->getAnimSwitch())
		{
			this->currentFrame.top = 75.f;
			this->currentFrame.left += 56.f;
			if (this->currentFrame.left >= 224.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(-1.5f, 1.5f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 1.5f, 0.f);
	}
	else if (this->animState == ULT && !this->castULT)
	{
		if (movingRight)
		{
			if (this->animationTimer.getElapsedTime().asMilliseconds() >= 190.f || this->getAnimSwitch())
			{
				this->currentFrame.top = 150.f;
				this->currentFrame.left += 56.f;
				if (this->currentFrame.left >= 504.f)
				{
					this->currentFrame.left = 0.f;
					this->animState = IDLE;
					this->castULT = true;
				}

				this->animationTimer.restart();
				this->sprite.setTextureRect(this->currentFrame);
			}
			this->sprite.setScale(1.5f, 1.5f);
			this->sprite.setOrigin(0.f, 0.f);
		}
		else if (movingLeft)
		{
			if (this->animationTimer.getElapsedTime().asMilliseconds() >= 190.f || this->getAnimSwitch())
			{
				this->currentFrame.top = 150.f;
				this->currentFrame.left += 56.f;
				if (this->currentFrame.left >= 504.f)
				{
					this->currentFrame.left = 0.f;
					this->animState = IDLE;
					this->castULT = true;
				}

				this->animationTimer.restart();
				this->sprite.setTextureRect(this->currentFrame);
			}
			this->sprite.setScale(-1.5f, 1.5f);
			this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 1.5f, 0.f);
		}
	}
	else
	{
		this->animationTimer.restart();
	}

	if (this->castULT)
	{
		if (movingRight)
		{
			if (this->animationTimer.getElapsedTime().asMilliseconds() >= 100.f)
			{
				this->ultCurrentFrame.top = 0.f;
				this->ultCurrentFrame.left += 256.f;
				if (this->ultCurrentFrame.left >= 2560.f)
				{
					this->ultCurrentFrame.left = 0;
					this->castULT = false;
					this->isCastingULT = false;
				}

				this->animationTimer.restart();
				this->ultSprite.setTextureRect(this->ultCurrentFrame);
			}
			this->ultSprite.setScale(1.5f, 1.5f);
			this->ultSprite.setOrigin(0.f, 0.f);
			this->ultSprite.setPosition(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width * 2.f,
				this->sprite.getPosition().y - (this->ultCurrentFrame.height));
		}
		else if(movingLeft)
		{
			if (this->animationTimer.getElapsedTime().asMilliseconds() >= 100.f)
			{
				this->ultCurrentFrame.top = 0.f;
				this->ultCurrentFrame.left += 256.f;
				if (this->ultCurrentFrame.left >= 2560.f)
				{
					this->ultCurrentFrame.left = 0;
					this->castULT = false;
					this->isCastingULT = false;
				}

				this->animationTimer.restart();
				this->ultSprite.setTextureRect(this->ultCurrentFrame);
			}
			this->ultSprite.setScale(-1.5f, 1.5f);
			this->ultSprite.setOrigin(0.f, 0.f);
			this->ultSprite.setPosition(this->sprite.getPosition().x - this->sprite.getGlobalBounds().width * 1.15f,
				this->sprite.getPosition().y - (this->ultCurrentFrame.height));
		}
	}

	
}

void Player::update()
{
	this->updateMovement();
	this->updateAttack();
	this->updateAnimations();
	this->updatePhysics();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	if (this->castULT)
	{
		target.draw(this->ultSprite);
	}
}
