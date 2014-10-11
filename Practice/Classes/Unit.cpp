#include "Unit.h"


Unit::Unit(const std::string& filename, BodyShape shape, Vect createPos)
{
	m_Speed = 100.0f;
	m_MoveMode = false;

	auto sprite = Sprite::create(filename);
	sprite->setScale(2.0f);

	// 밀도, 복원력, 마찰력
	auto material = PhysicsMaterial(1.0f, 0.6f, 0.8f);
	
	PhysicsBody* body = nullptr;
	switch (shape)
	{
	case CIRCLE:
		body = PhysicsBody::createCircle(sprite->getContentSize().width, material);
		break;
	case BOX:
		body = PhysicsBody::createBox(Size(sprite->getContentSize().width*2, sprite->getContentSize().height*2), material);
		break;
	}
	body->setMass(1.0f);
	body->setRotationEnable(false);
	body->setAngularDamping(1);
	body->setLinearDamping(3);

	sprite->setPhysicsBody(body);
	sprite->setPosition(createPos);
	

	m_Sprite	= sprite;
	m_Body		= body;
}

void Unit::moveTargeting(Point p)
{
	m_MoveMode = true;
	m_MovePosition = p;
}

void Unit::movement()
{
	if (m_MoveMode)
	{
		if (!(m_Body->getPosition().x < m_MovePosition.x - 5 ||
			m_Body->getPosition().y < m_MovePosition.y - 5 ||
			m_Body->getPosition().x > m_MovePosition.x + 5 ||
			m_Body->getPosition().y > m_MovePosition.y + 5))
		{
			m_MoveMode = false;
			m_Body->setVelocity(Vect::ZERO);
			return;
		}

		auto direction = m_MovePosition - m_Body->getPosition();
		auto temp = abs(direction.x) + abs(direction.y);
		
		direction *= m_Speed / temp;

		m_Body->applyImpulse(direction);
	}
}
