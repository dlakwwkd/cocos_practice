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
	case KEY_SPACE:
		gravity = Vect(0.0f, 0.0f);
		m_World->setGravity(gravity);
		GET_IM->setKeyStatus(KEY_SPACE, true);
		break;

	case KEY_UP_ARROW:		GET_IM->setKeyStatus(KEY_UP_ARROW, true);		break;
	case KEY_DOWN_ARROW:		GET_IM->setKeyStatus(KEY_DOWN_ARROW, true);	break;
	case KEY_RIGHT_ARROW:		GET_IM->setKeyStatus(KEY_RIGHT_ARROW, true);	break;
	case KEY_LEFT_ARROW:		GET_IM->setKeyStatus(KEY_LEFT_ARROW, true);	break;

	case KEY_Z:
		gravity = Vect(m_World->getGravity().x, -m_World->getGravity().y);
		m_World->setGravity(gravity);
		GET_IM->setKeyStatus(KEY_Z, true);
		break;
	case KEY_X:
		gravity = Vect(0.0f, -1000.0f);
		m_World->setGravity(gravity);
		GET_IM->setKeyStatus(KEY_X, true);
		break;
	}
}

void PhysicsLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case KEY_SPACE:		GET_IM->setKeyStatus(KEY_SPACE, false);	break;
	case KEY_UP_ARROW:		GET_IM->setKeyStatus(KEY_UP_ARROW, false);		break;
	case KEY_DOWN_ARROW:		GET_IM->setKeyStatus(KEY_DOWN_ARROW, false);	break;
	case KEY_RIGHT_ARROW:		GET_IM->setKeyStatus(KEY_RIGHT_ARROW, false);	break;
	case KEY_LEFT_ARROW:		GET_IM->setKeyStatus(KEY_LEFT_ARROW, false);	break;
	case KEY_Z:			GET_IM->setKeyStatus(KEY_Z, false);		break;
	case KEY_X:			GET_IM->setKeyStatus(KEY_X, false);		break;
	}
}

void PhysicsLayer::updateKeyInput()
{
	Vect temp;

	if (GET_IM->getKeyStatus(KEY_UP_ARROW))
	{
		this->setPositionY(this->getPositionY() - 10);
	}
	if (GET_IM->getKeyStatus(KEY_DOWN_ARROW))
	{
		this->setPositionY(this->getPositionY() + 10);
	}
	if (GET_IM->getKeyStatus(KEY_LEFT_ARROW))
	{
		this->setPositionX(this->getPositionX() + 10);
	}
	if (GET_IM->getKeyStatus(KEY_RIGHT_ARROW))
	{
		this->setPositionX(this->getPositionX() - 10);
	}
}

void PhysicsLayer::cameraSync()
{
	
}
