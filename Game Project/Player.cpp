#include "Player.h"
#include "CollisionManager.h"
using namespace std;

Player::Player() : SDLGameObject(), target(0,0)
{

}

void Player::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	if (jStart > -5)
	{
		if (Player::getPosition().getY() < (jStart - 40)){
			jumping = false;
			falling = true;
			jStart = -5;
		}
	}
	if (!jumping) m_velocity.setY(2);
	m_velocity.setX(0);
	

	handleInput();
	handleAnimation();
	
	SDLGameObject::update();
	bool left = false;
	bool right = false;
	bool top = false;
	bool bottom = false;
	if (Player::getPosition().getX() + Player::getWidth() > 640)
	{
		right = true;
	}

	if(Player::getPosition().getX() < 0)
	{
		left = true;
	}
	if (Player::getPosition().getY() + Player::getHeight() >480)
	{
		bottom = true;
		falling = false;
	}
	if (Player::getPosition().getY() < 0)
	{
		top = true;
	}
	
	if (left || right || top || bottom)
	{
		cout << "Player reached ";
		if (left)
		{
			cout << "left" << endl;
			Player::m_position.setX(0);
		}
		if (right)
		{
			cout << "right" << endl;
			Player::m_position.setX(640-Player::getWidth());
		}
		if (bottom)
		{
			cout << "bottom" << endl;
			Player::m_position.setY(480-Player::getHeight());
		}
		if (top)
		{
			cout << "top" << endl;
			Player::m_position.setY(0);
		}
	}
}
void Player::clean()
{
}

void Player::handleAnimation()
{
	if (SDL_GetTicks() - shootStart > 0 && SDL_GetTicks() - shootStart < 100 && shooting)
	{
		m_currentRow = 2;
		m_currentFrame = 0;
	}
	else if (standing)
	{
		m_currentRow = 1;
		m_currentFrame = 1;
	}
	else
	{
		m_currentRow = 1;
		m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

	}
}

void Player::handleInput()
{	
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A) || TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D))
	{
		standing = false;
	}
	else
	{
		standing = true;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D))
	{
		move(MRIGHT);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
	{
		move(MLEFT);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W))
	{
		move(MJUMP);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
	{
		shoot();
	}
}

void Player::move(int dir)
{
	// get the current position
	Vector2D newPos = m_position;
	switch (dir){
	case MRIGHT:
		m_velocity.setX(2);
		newPos.m_x = m_position.m_x + m_velocity.m_x;
		if (!checkCollideTile(newPos))
		{
			// no collision, add to the actual x position
			m_position.m_x = newPos.m_x;
		}
		else
		{
			// collision, stop x movement
			m_velocity.m_x = 0;
		}
		break;
	case MLEFT:
		m_velocity.setX(-2);
		break;
	case MJUMP:
		if (jumping || falling) break;
		jumping = true;
		jStart = Player::getPosition().getY();
		m_velocity.setY(-4);
		break;
	}
}

void Player::shoot()
{
	shooting = true;
	shootStart = SDL_GetTicks();
}