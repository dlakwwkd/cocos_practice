#include "MapLayer.h"


bool MapLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto sprite = Sprite::create("Images/bg1.png");
	sprite->setPosition(this->getAnchorPointInPoints());
	this->addChild(sprite);

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto body = PhysicsBody::createEdgeBox(sprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPhysicsBody(body);
	edgeNode->setPosition(this->getAnchorPointInPoints());
	this->addChild(edgeNode);

	return true;
}
