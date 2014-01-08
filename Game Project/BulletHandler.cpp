#include "BulletHandler.h"
#include "Game.h"

BulletHandler* BulletHandler::s_pInstance = 0;
void BulletHandler::add(Vector2D pos)
{
	std::cout << pos.m_x << "," << pos.m_y << std::endl;
	bulletPos.push_back(pos);
}

std::vector< int > BulletHandler::get(int num)
{
	std::vector<int> temp;
	temp.push_back(bulletPos.at(num).m_x);
	temp.push_back(bulletPos.at(num).m_y);
	return temp;
}

void BulletHandler::update()
{
	for (int i = 0; i < bulletPos.size(); i++)
	{
		bulletPos.at(i) += bulletSpeed;
		if (bulletPos.at(i).m_x > TheGame::Instance()->getGameWidth())
		{
			//remove from array
		}
	}
}