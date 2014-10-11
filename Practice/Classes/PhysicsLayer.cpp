#include "PhysicsLayer.h"
#include "MapLayer.h"
#include "ObjectLayer.h"
#include "GameManager.h"
#include "Enums.h"


bool PhysicsLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto layer1 = MapLayer::create();
	this->addChild(layer1, 0, MAP_LAYER);
	auto layer2 = ObjectLayer::create();
	this->addChild(layer2, 1, OBJECT_LAYER);

	auto MouseListener = EventListenerMouse::create();
	MouseListener->onMouseDown = CC_CALLBACK_1(PhysicsLayer::onMouseDown, this);
	MouseListener->onMouseUp = CC_CALLBACK_1(PhysicsLayer::onMouseUp, this);
	MouseListener->onMouseMove = CC_CALLBACK_1(PhysicsLayer::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(MouseListener, this);

	auto *K_listener = EventListenerKeyboard::create();
	K_listener->onKeyPressed = CC_CALLBACK_2(PhysicsLayer::onKeyPressed, this);
	K_listener->onKeyReleased = CC_CALLBACK_2(PhysicsLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(K_listener, this);

	this->schedule(schedule_selector(PhysicsLayer::tick));
	return true;
}

void PhysicsLayer::tick(float dt)
{
	updateKeyInput();
	cameraSync();
	auto child = (ObjectLayer*)(this->getChildByTag(OBJECT_LAYER));
	child->MobAi();
}

void PhysicsLayer::onMouseDown(Event *event)
{
	auto button = ((EventMouse*)event)->getMouseButton();
	switch (button)
	{
	case MOUSE_BUTTON_LEFT:
		GET_IM->setMouseStatus(MOUSE_BUTTON_LEFT, true);
		break;
	case MOUSE_BUTTON_RIGHT:
		auto child = (ObjectLayer*)(this->getChildByTag(OBJECT_LAYER));
		child->unitMove(GET_IM->getMouseLocation());
		break;
	}
}

void PhysicsLayer::onMouseUp(Event *event)
{
	GET_IM->setMouseStatus(MOUSE_BUTTON_LEFT, false);
}

void PhysicsLayer::onMouseMove(Event *event)
{
	auto temp = ((EventMouse*)event)->getLocation();
	temp.y = Director::getInstance()->getWinSize().height - temp.y;

	GET_IM->setMouseLocation(temp);

	
	if (GET_IM->getMouseStatus(MOUSE_BUTTON_LEFT))
	{
		auto child = (ObjectLayer*)(this->getChildByTag(OBJECT_LAYER));
		child->addNewSpriteAtPosition(GET_IM->getMouseLocation());
	}
}


void PhysicsLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto gravity = Vect(0.0f, 0.0f);

	switch (keyCode)
	{
	case SPACE_KEY:
		gravity = Vect(0.0f, 0.0f);
		m_World->setGravity(gravity);
		GET_IM->setKeyStatus(SPACE_KEY, true);
		break;

	case UP_KEY:		GET_IM->setKeyStatus(UP_KEY, true);		break;
	case DOWN_KEY:		GET_IM->setKeyStatus(DOWN_KEY, true);	break;
	case RIGHT_KEY:		GET_IM->setKeyStatus(RIGHT_KEY, true);	break;
	case LEFT_KEY:		GET_IM->setKeyStatus(LEFT_KEY, true);	break;

	case Z_KEY:
		gravity = Vect(m_World->getGravity().x, -m_World->getGravity().y);
		m_World->setGravity(gravity);
		GET_IM->setKeyStatus(Z_KEY, true);
		break;
	case X_KEY:
		gravity = Vect(0.0f, -1000.0f);
		m_World->setGravity(gravity);
		GET_IM->setKeyStatus(X_KEY, true);
		break;
	}
}

void PhysicsLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case SPACE_KEY:		GET_IM->setKeyStatus(SPACE_KEY, false);	break;
	case UP_KEY:		GET_IM->setKeyStatus(UP_KEY, false);		break;
	case DOWN_KEY:		GET_IM->setKeyStatus(DOWN_KEY, false);	break;
	case RIGHT_KEY:		GET_IM->setKeyStatus(RIGHT_KEY, false);	break;
	case LEFT_KEY:		GET_IM->setKeyStatus(LEFT_KEY, false);	break;
	case Z_KEY:			GET_IM->setKeyStatus(Z_KEY, false);		break;
	case X_KEY:			GET_IM->setKeyStatus(X_KEY, false);		break;
	}
}

void PhysicsLayer::updateKeyInput()
{
	Vect temp;

	if (GET_IM->getKeyStatus(UP_KEY))
	{
		this->setPositionY(this->getPositionY() - 10);
		//m_Hero->applyImpulse(Vect(0, 10));
	}
	if (GET_IM->getKeyStatus(DOWN_KEY))
	{
		this->setPositionY(this->getPositionY() + 10);
		//m_Hero->applyImpulse(Vect(0, -10));
	}
	if (GET_IM->getKeyStatus(LEFT_KEY))
	{
		this->setPositionX(this->getPositionX() + 10);
		//m_Hero->applyImpulse(Vect(10, 0));
	}
	if (GET_IM->getKeyStatus(RIGHT_KEY))
	{
		this->setPositionX(this->getPositionX() - 10);
		//m_Hero->applyImpulse(Vect(-10, 0));
	}
}

void PhysicsLayer::cameraSync()
{
	
}
