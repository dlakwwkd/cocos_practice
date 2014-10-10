#pragma once
#include "cocos2d.h"

USING_NS_CC;

#define SPACE_KEY		EventKeyboard::KeyCode::KEY_SPACE
#define UP_KEY			EventKeyboard::KeyCode::KEY_UP_ARROW
#define DOWN_KEY		EventKeyboard::KeyCode::KEY_DOWN_ARROW
#define LEFT_KEY		EventKeyboard::KeyCode::KEY_LEFT_ARROW
#define RIGHT_KEY		EventKeyboard::KeyCode::KEY_RIGHT_ARROW
#define ENTER_KEY		EventKeyboard::KeyCode::KEY_ENTER
#define Z_KEY			EventKeyboard::KeyCode::KEY_Z
#define X_KEY			EventKeyboard::KeyCode::KEY_X

class InputManager
{
public:
	InputManager();

	Vect getMouseLocation()										{ return m_MouseLocation; }
	bool getMouseStatus(int button)								{ return m_MouseStatus[button]; }
	bool getKeyStatus(EventKeyboard::KeyCode key)				{ return m_KeyStatus[key]; }
	void setMouseLocation(Vect p)								{ m_MouseLocation = p; }
	void setMouseStatus(int button, bool status)				{ m_MouseStatus[button] = status; }
	void setKeyStatus(EventKeyboard::KeyCode key, bool status)	{ m_KeyStatus[key] = status; }

private:
	Vect									m_MouseLocation;
	std::map<int, bool>						m_MouseStatus;
	std::map<EventKeyboard::KeyCode, bool>	m_KeyStatus;
};