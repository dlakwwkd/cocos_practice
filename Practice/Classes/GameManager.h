#pragma once
#include "cocos2d.h"
#include "InputManager.h"

USING_NS_CC;

#define GET_GM GameManager::getInstance()
#define GET_IM GameManager::getInstance().getIM()

class GameManager
{
public:
	static GameManager& getInstance()
	{
		static GameManager instance;
		return instance;
	}
	//void clearManagers(){ delete m_IM; }
	std::shared_ptr<InputManager> getIM(){ return m_IM; }

private:
	GameManager();
	std::shared_ptr<InputManager> m_IM;


};