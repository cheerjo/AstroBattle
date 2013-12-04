#pragma once

#include <SDL.h>
#include "TextureManager.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class Game
{
public:
	//Return the instance
	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}

	~Game(){}

	//Initialise SDL
	bool init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen);

	//render objects
	void render();
	//update game state
	void update();
	//handle collisions / input etc
	void handleEvents();
	//clean up
	void clean();
	//quit (calls SDL_Quit())
	void quit();

	//function to access private running variable
	bool running(){
		return m_bRunning;
	}

	SDL_Renderer* getRenderer() const { return m_pRenderer; }

private:
	Game();
	static Game* s_pInstance;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	bool m_bRunning;
	int m_currentFrame;
	GameObject* m_go;
	GameObject* m_player;
	GameObject* m_enemy;
	std::vector<GameObject*> m_gameObjects;
};
typedef Game TheGame;