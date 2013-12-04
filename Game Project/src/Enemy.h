#include "SDLGameObject.h"
#pragma once
#ifndef __Enemy__
#define __Enemy__
class Enemy : public SDLGameObject
{
public:
	Enemy(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();
};

#endif