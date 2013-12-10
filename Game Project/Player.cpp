#include "Player.h"
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
	m_velocity.setX(0);
	m_velocity.setY(0);

	handleInput();

	m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

	SDLGameObject::update();
	bool left = false;
	bool right = false;
	if (Player::getPosition().getX() + Player::getWidth() > 640)
	{
		right = true;
	}

	if(Player::getPosition().getX() < 0)
	{
		left = true;
	}
	if (left || right)
	{
		cout << "Player reached x edge";
		if (left)
		{
			Player::m_position.setX(0);
		}
		if (right)
		{
			Player::m_position.setX(640-Player::getWidth());
		}
	}
}
void Player::clean()
{
}
void Player::handleInput()
{	
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_velocity.setX(2);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		m_velocity.setX(-2);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		m_velocity.setY(-2);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	{
		m_velocity.setY(2);
	}
}