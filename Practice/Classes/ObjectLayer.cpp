#include "ObjectLayer.h"
#include "PhysicsLayer.h"
#include "GameManager.h"
#include "Unit.h"


bool ObjectLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_Hero = nullptr;
	createHero({ 200, 200 });

	this->schedule(schedule_selector(ObjectLayer::tick));
	return true;
}

void ObjectLayer::tick(float dt)
{
	m_Hero->movement();
}

void ObjectLayer::unitMove(Point p)
{
	if (m_Hero == nullptr) return;

	m_Hero->moveTargeting(p);

// 	auto vect = m_Hero->getBody()->getPosition();
// 	vect = GET_IM->getMouseLocation() - vect;
// 
// 	m_Hero->getBody()->setVelocity(vect);
}

void ObjectLayer::createHero(Point location)
{
	std::shared_ptr<Unit> unit(new Unit("Images/pattern1.png", BOX, location));
	m_Hero = unit;
	m_Hero->getBody()->setVelocityLimit(100);
	this->addChild(m_Hero->getSprite());
}

void ObjectLayer::addNewSpriteAtPosition(Point p)
{
	auto parent = (PhysicsLayer*)(this->getParent());
	std::shared_ptr<Unit> unit(new Unit("Images/r2.png", CIRCLE, p - parent->getPosition()));
	unit->getBody()->setVelocityLimit(1000);

	m_MobList.push_back(unit);
	this->addChild(unit->getSprite());
}

void ObjectLayer::MobAi()
{
	auto winSize = Director::getInstance()->getWinSize();
	auto parent = (PhysicsLayer*)(this->getParent());

	for (auto& b : parent->getPhyWorld()->getAllBodies())
	{
		if (b == m_Hero->getBody()) continue;

		Vect temp;
		temp.x = rand() % (int)winSize.width;
		temp.y = rand() % (int)winSize.height;

		auto time = rand() % 300;

		if (time < 3)
			temp = temp - b->getPosition();
		else if (time == 10)
			temp = m_Hero->getBody()->getPosition() - b->getPosition();
		else
			continue;

		b->applyImpulse(temp*5);
	}
}
