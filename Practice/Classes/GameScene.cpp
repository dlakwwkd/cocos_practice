#include "GameScene.h"
#include <time.h>
#include <random>

#define PTM_RATIO 32

Scene* GameScene::createScene()
{
	auto *scene = Scene::create();
	auto *layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if(!Layer::init())
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	m_TextureSprite = TextureCache::sharedTextureCache()->addImage("CloseNormal.png");

	b2Vec2 gravity = b2Vec2(0.0f, -30.0f);
	world = new b2World(gravity);
	
	bool isBox2DDebugState = true;
	if(isBox2DDebugState) {
		auto box2DDebugDrawLayer = Box2DDebugDrawLayer::create(world, PTM_RATIO);
		this->addChild(box2DDebugDrawLayer, 10000);
	}

	m_IsSpace_KeyDown	= false;
	m_IsRight_KeyDown	= false;
	m_IsLeft_KeyDown	= false;
	m_IsUp_KeyDown		= false;
	m_IsDown_KeyDown	= false;
	m_IsZ_KeyDown		= false;
	m_IsX_KeyDown		= false;

	srand((unsigned int)time(NULL));

	this->schedule(schedule_selector(GameScene::tick));

	return true;
}

void GameScene::tick(float dt)
{
	int velocityiterations = 3;
	int positioninterations = 8;

	world->Step(dt, velocityiterations, positioninterations);

	for(b2Body *b = world->GetBodyList(); b; b=b->GetNext()) {
		if(b->GetUserData() != NULL) {
			auto *spriteData = (Sprite *)b->GetUserData();
			spriteData->setPosition(Point(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
	updateKeyInput();
	MobAi();
}

void GameScene::addNewSpriteAtPosition(Point location)
{
	auto sprite = Sprite::createWithTexture(m_TextureSprite, CCRectMake(0,0, m_TextureSprite->getContentSize().width, m_TextureSprite->getContentSize().height));
	sprite->setPosition(location.x, location.y);
	this->addChild(sprite);

	b2BodyDef bodyDef;
	bodyDef.position.Set(location.x/PTM_RATIO, location.y/PTM_RATIO);
	bodyDef.type = b2_dynamicBody;
	bodyDef.userData = sprite;

	b2Body *body = world->CreateBody(&bodyDef);

	b2CircleShape myshape;
	myshape.m_radius = 0.45;

	b2FixtureDef fixture;
	fixture.shape = &myshape;
	fixture.density = 1.0f;
	fixture.friction = 0.2f;
	fixture.restitution = 0.6f;

	body->CreateFixture(&fixture);
}

void GameScene::createHero(Point location)
{
	auto sprite = Sprite::createWithTexture(m_TextureSprite, CCRectMake(0, 0, m_TextureSprite->getContentSize().width, m_TextureSprite->getContentSize().height));
	sprite->setPosition(location.x, location.y);
	this->addChild(sprite);

	b2BodyDef bodyDef;
	bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
	bodyDef.type = b2_dynamicBody;
	bodyDef.userData = sprite;

	b2Body *body = world->CreateBody(&bodyDef);
	
	b2PolygonShape myshape;
	myshape.SetAsBox((sprite->getContentSize().width / 2) / PTM_RATIO,
					(sprite->getContentSize().height / 2) / PTM_RATIO);

	b2FixtureDef fixture;
	fixture.shape = &myshape;
	fixture.density = 2.0f;
	fixture.friction = 10.2f;
	fixture.restitution = 0.2f;

	body->CreateFixture(&fixture);
	m_Hero = body;
}

void GameScene::MobAi()
{
	auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();

	for (b2Body *b = world->GetBodyList(); b; b = b->GetNext()) 
	{
		auto tempX = rand() % (int)frameSize.width / PTM_RATIO;
		auto tempY = rand() % (int)frameSize.height / PTM_RATIO;

		if (b->GetUserData() != NULL && b != m_Hero)
		{
			b2Vec2 temp;
			auto time = rand() % 300;

			if (time < 3)
			{
				temp.x = (tempX - b->GetPosition().x*2);
				temp.y = (tempY - b->GetPosition().y*2);
			}
			else if (time == 10)
			{
				temp.x = (m_Hero->GetPosition().x - b->GetPosition().x)*5;
				temp.y = (m_Hero->GetPosition().y - b->GetPosition().y)*5;
			}
			else
			{
				continue;
			}
			b->SetLinearVelocity(temp);
		}
	}
}

void GameScene::onEnter()
{
	b2BodyDef groundDef;
	groundDef.position.Set(0,0);
	b2Body *ground = world->CreateBody(&groundDef);

	b2FixtureDef boxEdge;
	b2EdgeShape edgeShape;
	boxEdge.shape = &edgeShape;

	auto winSize = Director::getInstance()->getWinSize();
	auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();

	edgeShape.Set(b2Vec2(0, 0), b2Vec2(frameSize.width/PTM_RATIO, 0));
	ground->CreateFixture(&boxEdge);
	edgeShape.Set(b2Vec2(0, 0), b2Vec2(0, frameSize.height/PTM_RATIO));
	ground->CreateFixture(&boxEdge);
	edgeShape.Set(b2Vec2(0, frameSize.height/PTM_RATIO), b2Vec2(frameSize.width/PTM_RATIO, frameSize.height/PTM_RATIO));
	ground->CreateFixture(&boxEdge);
	edgeShape.Set(b2Vec2(frameSize.width/PTM_RATIO, 0), b2Vec2(frameSize.width/PTM_RATIO, frameSize.height/PTM_RATIO));
	ground->CreateFixture(&boxEdge);

	Layer::onEnter();

	createHero({200,200});

	auto *listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto *K_listener = EventListenerKeyboard::create();
	K_listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	K_listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(K_listener, this);
}

void GameScene::onExit()
{
	Layer::onExit();
}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	Point mylocation = touch->getLocation();
	addNewSpriteAtPosition(mylocation);
	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event)
{
	Point mylocation = touch->getLocation();
	addNewSpriteAtPosition(mylocation);
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	b2Vec2 gravity = b2Vec2(0.0f, 0.0f);

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		gravity = b2Vec2(0.0f, 0.0f);
		world->SetGravity(gravity);
		m_IsSpace_KeyDown = true;
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:		m_IsUp_KeyDown		= true;	break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:	m_IsDown_KeyDown	= true;	break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:	m_IsRight_KeyDown	= true;	break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:	m_IsLeft_KeyDown	= true;	break;

	case EventKeyboard::KeyCode::KEY_Z:
		gravity = b2Vec2(world->GetGravity().x, -world->GetGravity().y);
		world->SetGravity(gravity);
		m_IsZ_KeyDown = true;
		break;
	case EventKeyboard::KeyCode::KEY_X:
		gravity = b2Vec2(0.0f, -30.0f);
		world->SetGravity(gravity);
		m_IsX_KeyDown = true;
		break;
	}
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:			m_IsSpace_KeyDown	= false;	break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:		m_IsUp_KeyDown		= false;	break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:	m_IsDown_KeyDown	= false;	break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:	m_IsRight_KeyDown	= false;	break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:	m_IsLeft_KeyDown	= false;	break;
	case EventKeyboard::KeyCode::KEY_Z:				m_IsZ_KeyDown		= false;	break;
	case EventKeyboard::KeyCode::KEY_X:				m_IsX_KeyDown		= false;	break;
	}
}

void GameScene::updateKeyInput()
{
	if (m_Hero->GetUserData() != NULL) 
	{
		b2Vec2 temp;

		if (m_IsUp_KeyDown)
		{
			temp.x = m_Hero->GetLinearVelocity().x;
			temp.y = m_Hero->GetLinearVelocity().y + 1;
			m_Hero->SetLinearVelocity(temp);
		}
		if (m_IsDown_KeyDown)
		{
			temp.x = m_Hero->GetLinearVelocity().x;
			temp.y = m_Hero->GetLinearVelocity().y - 1;
			m_Hero->SetLinearVelocity(temp);
		}
		if (m_IsRight_KeyDown)
		{
			temp.x = m_Hero->GetLinearVelocity().x + 1;
			temp.y = m_Hero->GetLinearVelocity().y;
			m_Hero->SetLinearVelocity(temp);
		}
		if (m_IsLeft_KeyDown)
		{
			temp.x = m_Hero->GetLinearVelocity().x - 1;
			temp.y = m_Hero->GetLinearVelocity().y;
			m_Hero->SetLinearVelocity(temp);
		}
	}
}

