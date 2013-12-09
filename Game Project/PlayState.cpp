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

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());
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
	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	
	std::cout << "Exiting PlayState\n";
	return GameState::onExit();
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB,
		rightA, rightB,
		topA, topB,
		bottomA, bottomB;

	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();

	//If any sides from A are outside B
	if (bottomA <= topB){ return false; }
	if (topA >= bottomB){ return false; }
	if (rightA <= leftB){ return false; }
	if (leftA >= rightB){ return false;	}

	return true;
}