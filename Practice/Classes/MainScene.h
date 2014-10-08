#pragma once
#include "cocos2d.h"
class MainScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MainScene);

	void doClick1(cocos2d::Ref* sender);
	void doClick2(cocos2d::Ref* sender);
	void doClick3(cocos2d::Ref* sender);


};

