#include "Game.h"
#include <SDL_image.h>
#include <iostream>
bool Game::init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	//init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		std::cout << "SDL init success\n";
		//if succeeded, create our window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

		// if the window creation succeeded, create window
		if (m_pWindow != 0)
		{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false;
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false;
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // sdl could not init
	}
	std::cout << "init success\n";
	m_bRunning = true;
	//loading
	if (!TheTextureManager::Instance()->load("assets/animate-alpha.png", "animate", m_pRenderer))
	{
		return false;
	}
	m_go.load(100, 100, 128, 82, "animate");
	m_player.load(300, 300, 129, 82, "animate");
	return true;
}
void Game::update()
{
	m_go.update();
	m_player.update();
}
void Game::render()
{

	//clear window to black
	SDL_RenderClear(m_pRenderer);

	m_go.draw(m_pRenderer);
	m_player.draw(m_pRenderer);

	//show window
	SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;

		default:
			break;
		}
	}
}