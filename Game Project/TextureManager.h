#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <map>
class TextureManager
{
public:
	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	//draw static image
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//draw frame

	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	std::map<std::string, SDL_Texture*> m_textureMap;
};

