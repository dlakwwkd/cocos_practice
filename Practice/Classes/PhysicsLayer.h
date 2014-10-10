#pragma once
#include "cocos2d.h"

USING_NS_CC;

class PhysicsLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(PhysicsLayer);

	void setPhyWorld(PhysicsWorld* world){ m_World = world; }
	void tick(float dt);


	void addNewSpriteAtPosition(Point p);
	void createHero(Point location);
	void updateKeyInput();
	void cameraSync();
	void MobAi();

protected:
	PhysicsWorld*	m_World;
	PhysicsBody*	m_Hero;



public:
	virtual void onMouseDown(Event *event);
	virtual void onMouseUp(Event *event);
	virtual void onMouseMove(Event *event);

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);


};

