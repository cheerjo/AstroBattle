#include "Level.h"
#include "TextureManager.h"7
#include "Game.h"

void Level::render()
{
	TheTextureManager::Instance()->draw("background", 0, 0, 640, 480, TheGame::Instance()->getRenderer());
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->render();
	}
}

void Level::update()
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->update();
	}
}