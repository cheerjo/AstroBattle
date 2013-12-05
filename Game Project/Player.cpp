#include "Player.h"
using namespace std;

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams), m_numFrames(pParams->getNumFrames())
{

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
}
void Player::clean()
{
}
void Player::handleInput()
{
	Vector2D* target = TheInputHandler::Instance()->getMousePosition();

	m_velocity = (*target - m_position);
	m_velocity /= 50;
}