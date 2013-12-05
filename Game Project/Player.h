#pragma once
#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Player :
	public SDLGameObject
{
public:
	Player();
	virtual void load(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	void handleInput();
};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Player();
	}
};