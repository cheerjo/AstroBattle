#pragma once
#include "GameState.h"
#include <vector>
#include "GameObject.h"
class Level;
class GameObject;

class PlayState :
	public GameState
{
	friend class Player;
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();
	
	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

	virtual std::string getStateID() const { return s_playID; }
	static void addOb(GameObject* newObj);

protected:
	static const std::string s_playID;
	std::vector<GameObject*> m_gameObjects;
	Level *pLevel;
};

