#pragma once

#include <SDL.h>
#include "TextureManager.h"
class Game
{
public:
	Game(){}
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

	//function to access private running variable
	bool running(){
		return m_bRunning;
	}

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	bool m_bRunning;
	int m_currentFrame;
	TextureManager m_textureManager;
};

