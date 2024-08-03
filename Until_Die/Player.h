#ifndef PLAYER_H
#define PLAYER_H

enum PLAYER_ANIMATIONS_STATES {IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING, TORNADO, ULT};

class Player
{
private:
	sf::Texture texture;
	sf::Texture ultTexture;
	sf::Texture tornadoTexture;
	sf::Sprite sprite;
	sf::Sprite ultSprite;
	sf::Sprite tornadoSprite;
	sf::Clock animationTimer;
	sf::Clock ultClock;
	sf::Time ultTimer;
	sf::Clock tornadoClock;
	sf::Time tornadoTimer;

	//Animation
	short animState;
	sf::IntRect currentFrame;
	sf::IntRect ultCurrentFrame;
	sf::IntRect tornadoCurrentFrame;
	bool animationSwitch;
	bool canJump;
	bool castULT;
	bool isCastingULT;
	bool castTornado;
	bool isCastingTornado;
	bool movingLeft;
	bool movingRight;
	bool canCastSpeel;

	//Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxY;

	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
	void initPhysics();

public:
	Player();
	~Player();

	const bool& getAnimSwitch();
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	
	void setPosition(const float x, const float y);
	void resetVelocityY();

	bool getCanJump();
	void setCanJump();

	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void jump();
	void updatePhysics();
	void updateMovement();
	void updateAttack();
	void updateAnimations();
	void update();
	void render(sf::RenderTarget& target);
};

#endif

