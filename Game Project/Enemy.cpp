#include "Enemy.h"
#include "CollisionManager.h"
#include "PlayState.h"
#include "TileLayer.h"
#include "GameStateMachine.h"
using namespace std;

Enemy::Enemy() : SDLGameObject(), target(0, 0)
{

}

void Enemy::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	if (jStart > -5)
	{
		if (Enemy::getPosition().getY() < (jStart - 40)){
			jumping = false;
			falling = true;
			jStart = -5;
		}
	}
	if (!jumping) m_velocity.setY(2);
	m_velocity.setX(0);


	handleInput();
	if (SDL_GetTicks() - shootStart > 0 && SDL_GetTicks() - shootStart < 100 && shooting)
	{
		m_currentRow = 2;
		m_currentFrame = 0;
	}
	else if (SDL_GetTicks() - shootStart > 100 && shooting)
	{
		shootStart = 0;
		shooting = false;
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


	SDLGameObject::update();
	bool left = false;
	bool right = false;
	bool top = false;
	bool bottom = false;
	if (Enemy::getPosition().getX() + Enemy::getWidth() > 640)
	{
		right = true;
	}

	if (Enemy::getPosition().getX() < 0)
	{
		left = true;
	}
	if (Enemy::getPosition().getY() + Enemy::getHeight() >480)
	{
		bottom = true;
		falling = false;
	}
	if (Enemy::getPosition().getY() < 0)
	{
		top = true;
	}

	if (left || right || top || bottom)
	{
		if (left)
		{
			cout << "left" << endl;
			Enemy::m_position.setX(0);
		}
		if (right)
		{
			cout << "right" << endl;
			Enemy::m_position.setX(640 - Enemy::getWidth());
		}
		if (bottom)
		{
			//cout << "bottom" << endl;
			Enemy::m_position.setY(480 - Enemy::getHeight());
		}
		if (top)
		{
			cout << "top" << endl;
			Enemy::m_position.setY(0);
		}
	}
}
void Enemy::clean()
{
}

void Enemy::handleAnimation()
{

}

void Enemy::handleInput()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) || TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		standing = false;
	}
	else
	{
		standing = true;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		move(MRIGHT);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		move(MLEFT);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		move(MJUMP);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		shoot();
	}
}

void Enemy::move(int dir)
{
	switch (dir){
	case MRIGHT:
		m_velocity.setX(2);
		break;
	case MLEFT:
		m_velocity.setX(-2);
		break;
	case MJUMP:
		if (jumping || falling) break;
		jumping = true;
		jStart = Enemy::getPosition().getY();
		m_velocity.setY(-4);
		break;
	}
}

void Enemy::shoot()
{
	if (shooting) return;
	shooting = true;
	shootStart = SDL_GetTicks();

}