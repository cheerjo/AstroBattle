#include "PlayState.h"
#include <iostream>
#include "TextureManager.h"
#include "Player.h"
#include "Game.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "MenuState.h"
#include "StateParser.h"
#include "LevelParser.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "TextManager.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_1))
	{
		LevelParser levelParser;
		pLevel = levelParser.parseLevel("assets/map1.tmx");
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_2))
	{
		LevelParser levelParser;
		pLevel = levelParser.parseLevel("assets/map2.tmx");
	}
	pLevel->update();

}

void PlayState::render()
{
	pLevel->render();
}

bool PlayState::onEnter()
{
	//parse the state
	LevelParser levelParser;
	pLevel = levelParser.parseLevel("assets/map1.tmx");
	std::cout << "Loading laser sound" << std::endl;
	TheSoundManager::Instance()->load("assets/LASER1.WAV", "laser", SOUND_SFX);
	std::cout << "Loading explode sound" << std::endl;
	TheSoundManager::Instance()->load("assets/bang.wav", "explosion", SOUND_SFX);
	std::cout << "entering PlayState\n";
	SDL_ShowCursor(1);
	return true;
}

bool PlayState::onExit()
{
	
	std::cout << "Exiting PlayState\n";
	SDL_ShowCursor(1);
	return GameState::onExit();
}

bool PlayState::checkCollision(Player* p1, Vector2D bullet)
{
	int leftA, leftB,
		rightA, rightB,
		topA, topB,
		bottomA, bottomB;

	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	leftB = bullet.m_x;
	rightB = bullet.m_x + 27;
	topB = bullet.m_y;
	bottomB = bullet.m_y + 14;

	//If any sides from A are outside B
	if (bottomA <= topB){ return false; }
	if (topA >= bottomB){ return false; }
	if (rightA <= leftB){ return false; }
	if (leftA >= rightB){ return false;	}

	return true;
}
bool PlayState::checkCollision(Enemy* p1, Vector2D bullet)
{
	int leftA, leftB,
		rightA, rightB,
		topA, topB,
		bottomA, bottomB;

	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	leftB = bullet.m_x;
	rightB = bullet.m_x + 27;
	topB = bullet.m_y;
	bottomB = bullet.m_y + 14;

	//If any sides from A are outside B
	if (bottomA <= topB){ return false; }
	if (topA >= bottomB){ return false; }
	if (rightA <= leftB){ return false; }
	if (leftA >= rightB){ return false; }

	return true;
}