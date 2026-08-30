#include "Bullet.h"
#include "Math/MathUtil.h"
#include "Core/Factory.h"
#include "Components/PhysicsComponent.h"

FACTORY_REGISTER(Bullet);


void Bullet::Update(float dt)
{
	nu::Vector2 forward{ 1.0f, 0.0f };
	nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * m_speed;
	m_life_timer.Decrement(dt);
	if (m_life_timer.IsElapsed()) m_destroyed = true;
	nu::PhysicsComponent* physicsComponent = GetComponent<nu::PhysicsComponent>();
	physicsComponent->SetVelocity(velocity);
	Actor::Update(dt);
}

void Bullet::Read(const nu::json::value_t& value)
{
	Actor::Read(value);

	m_life_timer.SetTimer(m_lifespan);
	JSON_READ_NAME(value, "speed", m_speed);
}


