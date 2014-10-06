#pragma once
#include "cocos2d.h"

USING_NS_CC;

class GameScene : public LayerColor
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

	PhysicsWorld* m_World;

	void setPhyWorld(PhysicsWorld* world){ m_World = world; }
	void tick(float dt);



public:
	virtual void onMouseDown(Event *event);
	virtual void onMouseUp(Event *event);
	virtual void onMouseMove(Event *event);
	virtual void onMouseScroll(Event *event);
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void addNewSpriteAtPosition(Point p);
	void createHero(Point location);
	void updateKeyInput();
	void MobAi();

	Vect m_MousePosition;
	bool m_IsMouseDown;
	PhysicsBody*	m_Hero;
	bool		m_IsUp_KeyDown;
	bool		m_IsDown_KeyDown;
	bool		m_IsRight_KeyDown;
	bool		m_IsLeft_KeyDown;
	bool		m_IsSpace_KeyDown;
	bool		m_IsZ_KeyDown;
	bool		m_IsX_KeyDown;
};

