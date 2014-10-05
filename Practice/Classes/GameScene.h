#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"
#include "BOX2DDebugDrawLayer.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

	virtual void onEnter();
	virtual void onExit();

	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchMoved(Touch *touch, Event *event);
	virtual void onTouchEnded(Touch *touch, Event *event);

	void tick(float dt);

	b2World *world;

public:
	void addNewSpriteAtPosition(Point location);
	void createHero(Point location);
	void updateKeyInput();
	void MobAi();

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	Texture2D*	m_TextureSprite;
	b2Body*		m_Hero;
	bool		m_IsUp_KeyDown;
	bool		m_IsDown_KeyDown;
	bool		m_IsRight_KeyDown;
	bool		m_IsLeft_KeyDown;
	bool		m_IsSpace_KeyDown;
	bool		m_IsZ_KeyDown;
	bool		m_IsX_KeyDown;
};

#endif 