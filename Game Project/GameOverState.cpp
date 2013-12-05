#include "GameOverState.h"
#include "StateParser.h"
#include "MenuButton.h"
#include <iostream>
#include "Game.h"
#include "AnimatedGraphic.h"
#include "PlayState.h"
#include "MainMenuState.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new
		PlayState());
}

void GameOverState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		
		m_gameObjects[i]->update();
	}
}

void GameOverState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool GameOverState::onExit()
{
	std::cout << "exiting GameOverState\n";
	return GameState::onExit();
}

bool GameOverState::onEnter()
{
	//parse the state
	StateParser stateParser;
	stateParser.parseState("test.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_gameOverToMain);
	m_callbacks.push_back(s_restartPlay);

	//set callbacks for menu items

	setCallbacks(m_callbacks);

	std::cout << "entering GameOverState\n";
	return true;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
	//go through game objects
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		//if of type MEnuButton, assign callback based on id passed from file
		if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton =
				dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}