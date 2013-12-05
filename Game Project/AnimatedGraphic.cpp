#include "AnimatedGraphic.h"
using namespace std;

AnimatedGraphic::AnimatedGraphic()
{
	
}
void AnimatedGraphic::load(const LoaderParams* pParams, int animSpeed)
{
	SDLGameObject::load(pParams);
}
void AnimatedGraphic::draw()
{
	SDLGameObject::draw();
}

void AnimatedGraphic::update()
{
	m_currentFrame = int(((SDL_GetTicks() / (1000/m_animSpeed)) % m_numFrames));

	SDLGameObject::update();
}
void AnimatedGraphic::clean()
{

}