#include "PhysicsLayer.h"
#include "GameManager.h"


bool PhysicsLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}


	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);

	createHero({ 200, 200 });

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
	//MobAi();
}

void PhysicsLayer::onMouseDown(Event *event)
{
	auto button = (static_cast<EventMouse*>(event))->getMouseButton();
	switch (button)
	{
	case MOUSE_BUTTON_LEFT:
		GET_IM->setMouseStatus(MOUSE_BUTTON_LEFT, true);
		break;
	case MOUSE_BUTTON_RIGHT:
		for (auto& b : m_World->getAllBodies())
		{
			auto vect = b->getPosition();
			vect = GET_IM->getMouseLocation() - vect;
			b->setVelocity(vect);
		}
		auto vect = m_Hero->getPosition();
		vect = GET_IM->getMouseLocation() - vect;

		m_Hero->setVelocity(vect);
		break;
	}
}

void PhysicsLayer::onMouseUp(Event *event)
{
	GET_IM->setMouseStatus(MOUSE_BUTTON_LEFT, false);
}

void PhysicsLayer::onMouseMove(Event *event)
{
	auto temp = (static_cast<EventMouse*>(event))->getLocation();
	temp.y = Director::getInstance()->getWinSize().height - temp.y;

	GET_IM->setMouseLocation(temp);

	
	if (GET_IM->getMouseStatus(MOUSE_BUTTON_LEFT))
	{
		addNewSpriteAtPosition(GET_IM->getMouseLocation());
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

void PhysicsLayer::createHero(Point location)
{
	auto sprite = Sprite::create("Images/pattern1.png");

	// 밀도, 복원력, 마찰력
	auto material = PhysicsMaterial(1.0f, 0.7f, 0.8f);

	auto body = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height), material);
	body->setMass(1.0f);
	body->setRotationEnable(true);
	body->setAngularDamping(1);
	body->setLinearDamping(1);

	sprite->setPhysicsBody(body);
	sprite->setPosition(location);
	m_Hero = body;

	this->addChild(sprite);
}

void PhysicsLayer::addNewSpriteAtPosition(Point p)
{
	auto sprite = Sprite::create("Images/CloseSelected.png");

	// 밀도, 복원력, 마찰력
	auto material = PhysicsMaterial(1.0f, 0.8f, 0.8f);

	auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2, material);
	body->setMass(0.3f);
	body->setRotationEnable(true);
	body->setAngularDamping(1);
	body->setLinearDamping(1);

	sprite->setPhysicsBody(body);
	sprite->setPosition(p - this->getPosition());

	this->addChild(sprite);
}


void PhysicsLayer::MobAi()
{
	auto winSize = Director::getInstance()->getWinSize();

	for (auto& b : m_World->getAllBodies())
	{
		if (b == m_Hero) continue;
		
		Vect temp;
		temp.x = rand() % (int)winSize.width;
		temp.y = rand() % (int)winSize.height;

		auto time = rand() % 300;

		if (time < 3)
			temp = temp - b->getPosition();
		else if (time == 10)
			temp = m_Hero->getPosition() - b->getPosition();
		else
			continue;

		b->applyImpulse(temp);
	}
}
