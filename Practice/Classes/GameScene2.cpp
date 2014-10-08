#include "GameScene2.h"


Scene* GameScene2::createScene()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	scene->getPhysicsWorld()->setGravity(Vect::ZERO);

	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	scene->addChild(edgeNode);

	auto layer = GameScene2::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}

bool GameScene2::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 0)))
	{
		return false;
	}

	m_IsMouseDown = false;
	m_IsSpace_KeyDown = false;
	m_IsRight_KeyDown = false;
	m_IsLeft_KeyDown = false;
	m_IsUp_KeyDown = false;
	m_IsDown_KeyDown = false;
	m_IsZ_KeyDown = false;
	m_IsX_KeyDown = false;

	auto MouseListener = EventListenerMouse::create();
	MouseListener->onMouseDown = CC_CALLBACK_1(GameScene2::onMouseDown, this);
	MouseListener->onMouseUp = CC_CALLBACK_1(GameScene2::onMouseUp, this);
	MouseListener->onMouseMove = CC_CALLBACK_1(GameScene2::onMouseMove, this);
	MouseListener->onMouseScroll = CC_CALLBACK_1(GameScene2::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(MouseListener, this);

	auto *K_listener = EventListenerKeyboard::create();
	K_listener->onKeyPressed = CC_CALLBACK_2(GameScene2::onKeyPressed, this);
	K_listener->onKeyReleased = CC_CALLBACK_2(GameScene2::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(K_listener, this);

	createHero({ 200, 200 });
	this->schedule(schedule_selector(GameScene2::tick));

	return true;
}

void GameScene2::tick(float dt)
{
	updateKeyInput();
	groundFriction();
}

void GameScene2::onMouseDown(Event *event)
{
	auto button = (static_cast<EventMouse*>(event))->getMouseButton();
	switch (button)
	{
	case MOUSE_BUTTON_LEFT:	m_IsMouseDown = true;	break;
	case MOUSE_BUTTON_RIGHT:
		for (auto& b : m_World->getAllBodies())
		{
			auto vect = b->getPosition();
			vect.x = m_MousePosition.x - vect.x;
			vect.y = m_MousePosition.y - vect.y;
			b->setVelocity(vect);
		}
		auto vect = m_Hero->getPosition();
		vect.x = m_MousePosition.x - vect.x;
		vect.y = m_MousePosition.y - vect.y;

		// 		auto temp = abs(vect.x) + abs(vect.y);
		// 		vect.x /= temp/1000;
		// 		vect.y /= temp/1000;
		m_Hero->setVelocity(vect);
		break;
	}
}

void GameScene2::onMouseUp(Event *event)
{
	m_IsMouseDown = false;
}

void GameScene2::onMouseMove(Event *event)
{
	m_MousePosition = (static_cast<EventMouse*>(event))->getLocation();
	m_MousePosition.y = Director::getInstance()->getWinSize().height - m_MousePosition.y;

	if (m_IsMouseDown)
	{
		addNewSpriteAtPosition(m_MousePosition);
	}
}

void GameScene2::onMouseScroll(Event *event)
{

}


void GameScene2::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto gravity = Vect(0.0f, 0.0f);

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		gravity = Vect(0.0f, 0.0f);
		m_World->setGravity(gravity);
		m_IsSpace_KeyDown = true;
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:		m_IsUp_KeyDown = true;	break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:	m_IsDown_KeyDown = true;	break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:	m_IsRight_KeyDown = true;	break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:	m_IsLeft_KeyDown = true;	break;

	case EventKeyboard::KeyCode::KEY_Z:
		gravity = Vect(m_World->getGravity().x, -m_World->getGravity().y);
		m_World->setGravity(gravity);
		m_IsZ_KeyDown = true;
		break;
	case EventKeyboard::KeyCode::KEY_X:
		gravity = Vect(0.0f, -1000.0f);
		m_World->setGravity(gravity);
		m_IsX_KeyDown = true;
		break;
	}
}

void GameScene2::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:			m_IsSpace_KeyDown = false;	break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:		m_IsUp_KeyDown = false;	break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:	m_IsDown_KeyDown = false;	break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:	m_IsRight_KeyDown = false;	break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:	m_IsLeft_KeyDown = false;	break;
	case EventKeyboard::KeyCode::KEY_Z:				m_IsZ_KeyDown = false;	break;
	case EventKeyboard::KeyCode::KEY_X:				m_IsX_KeyDown = false;	break;
	}
}

void GameScene2::updateKeyInput()
{
	Vect temp;

	if (m_IsUp_KeyDown)
	{
		//this->setPositionY(this->getPositionY() - 10);
		temp.x = m_Hero->getVelocity().x;
		temp.y = m_Hero->getVelocity().y + 100;
		m_Hero->setVelocity(temp);
	}
	if (m_IsDown_KeyDown)
	{
		//this->setPositionY(this->getPositionY() + 10);
		temp.x = m_Hero->getVelocity().x;
		temp.y = m_Hero->getVelocity().y - 100;
		m_Hero->setVelocity(temp);
	}
	if (m_IsRight_KeyDown)
	{
		//this->setPositionX(this->getPositionX() - 10);
		temp.x = m_Hero->getVelocity().x + 100;
		temp.y = m_Hero->getVelocity().y;
		m_Hero->setVelocity(temp);
	}
	if (m_IsLeft_KeyDown)
	{
		//this->setPositionX(this->getPositionX() + 10);
		temp.x = m_Hero->getVelocity().x - 100;
		temp.y = m_Hero->getVelocity().y;
		m_Hero->setVelocity(temp);
	}
}

void GameScene2::createHero(Point location)
{
	auto sprite = Sprite::create("Images/pattern1.png");

	// 밀도, 복원력, 마찰력
	auto material = PhysicsMaterial(1.0f, 0.6f, 1.8f);

	auto body = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height), material);
	body->setMass(1000.0f);

	sprite->setPhysicsBody(body);
	sprite->setPosition(location);
	m_Hero = body;

	this->addChild(sprite);
}

void GameScene2::addNewSpriteAtPosition(Point p)
{
	auto sprite = Sprite::create("Images/CloseSelected.png");
	sprite->setPosition(p);

	// 밀도, 복원력, 마찰력
	auto material = PhysicsMaterial(1.0f, 0.8f, 0.8f);

	auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2, material);
	body->setMass(1.0f);
	body->setRotationEnable(false);

	sprite->setPhysicsBody(body);

	this->addChild(sprite);
}


void GameScene2::MobAi()
{
// 	auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
// 
// 	for (b2Body *b = world->GetBodyList(); b; b = b->GetNext()) 
// 	{
// 		auto tempX = rand() % (int)frameSize.width / PTM_RATIO;
// 		auto tempY = rand() % (int)frameSize.height / PTM_RATIO;
// 
// 		if (b->GetUserData() != NULL && b != m_Hero)
// 		{
// 			b2Vec2 temp;
// 			auto time = rand() % 300;
// 
// 			if (time < 3)
// 			{
// 				temp.x = (tempX - b->GetPosition().x*2);
// 				temp.y = (tempY - b->GetPosition().y*2);
// 			}
// 			else if (time == 10)
// 			{
// 				temp.x = (m_Hero->GetPosition().x - b->GetPosition().x)*5;
// 				temp.y = (m_Hero->GetPosition().y - b->GetPosition().y)*5;
// 			}
// 			else
// 			{
// 				continue;
// 			}
// 			b->SetLinearVelocity(temp);
// 		}
// 	}
}

void GameScene2::groundFriction()
{
	for (auto& b : m_World->getAllBodies())
	{
		auto vect = b->getVelocity();

		auto temp = sqrt(pow(vect.x, 2) + pow(vect.y, 2));
		if (abs(vect.x) > 0)
			vect.x -= vect.x / sqrt(temp);
		if (abs(vect.y) > 0)
			vect.y -= vect.y / sqrt(temp);

		b->setVelocity(vect);
	}
}
