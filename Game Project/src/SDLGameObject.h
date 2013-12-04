#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"
#include "Game.h"
#ifndef __SDLGameObject__
#define __SDLGameObject__
#pragma once
class SDLGameObject : public GameObject
{
public:
	SDLGameObject(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean(){}

protected:
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	int m_height;
	int m_width;

	int m_currentRow;
	int m_currentFrame;

	std::string m_textureID;
};

#endif
