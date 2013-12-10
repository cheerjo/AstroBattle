#pragma once
#include "SDLGameObject.h"
#include "GameObjectFactory.h"
class TileLayer;
class Player :
	public SDLGameObject
{
public:
	Player();
	virtual void load(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	Vector2D getVelocity() { return m_velocity; }
	virtual void collision(){ std::cout << "collision!"; }

private:
	void handleInput();
	Vector2D target;
};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Player();
	}
};