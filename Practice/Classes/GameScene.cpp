#include "GameScene.h"
#include "PhysicsLayer.h"
#include "UILayer.h"
#include "Enums.h"

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	scene->getPhysicsWorld()->setGravity(Vect::ZERO);

	auto layer = GameScene::create();
	scene->addChild(layer, 0, DEFAULT_LAYER);

	auto layer2 = PhysicsLayer::create();
	layer2->setPhyWorld(scene->getPhysicsWorld());
	layer->addChild(layer2, 0, PHYSICS_LAYER);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

// 	auto layer = UILayer::create();
// 	this->addChild(layer, 10, UI_LAYER);

	return true;
}