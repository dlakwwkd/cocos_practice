#pragma once
#include "cocos2d.h"

USING_NS_CC;

#define KEY_ENTER			EventKeyboard::KeyCode::KEY_ENTER
#define KEY_SPACE			EventKeyboard::KeyCode::KEY_SPACE
#define KEY_UP_ARROW		EventKeyboard::KeyCode::KEY_UP_ARROW
#define KEY_DOWN_ARROW		EventKeyboard::KeyCode::KEY_DOWN_ARROW
#define KEY_LEFT_ARROW		EventKeyboard::KeyCode::KEY_LEFT_ARROW
#define KEY_RIGHT_ARROW		EventKeyboard::KeyCode::KEY_RIGHT_ARROW
#define KEY_Z				EventKeyboard::KeyCode::KEY_Z
#define KEY_X				EventKeyboard::KeyCode::KEY_X

class InputManager
{
public:
	InputManager();

	Point	getMouseLocation()										{ return m_MouseLocation; }
	bool	getMouseStatus(int button)								{ return m_MouseStatus[button]; }
	bool	getKeyStatus(EventKeyboard::KeyCode key)				{ return m_KeyStatus[key]; }
	
	void	setMouseLocation(Point p)								{ m_MouseLocation = p; }
	void	setMouseStatus(int button, bool status)					{ m_MouseStatus[button] = status; }
	void	setKeyStatus(EventKeyboard::KeyCode key, bool status)	{ m_KeyStatus[key] = status; }

private:
	Point									m_MouseLocation;
	std::map<int, bool>						m_MouseStatus;
	std::map<EventKeyboard::KeyCode, bool>	m_KeyStatus;
};