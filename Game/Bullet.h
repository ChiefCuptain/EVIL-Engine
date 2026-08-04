#pragma once

#include "Actor.h"

struct BulletDesc : public nu::ActorDesc
{
	float speed = 0.0f;
};

class Bullet : public nu::Actor
{
public:
	Bullet() = default;
	Bullet(const BulletDesc& BulletDesc) :
		Actor{ BulletDesc },
		m_speed{ BulletDesc.speed }
	{}


	void Update(float dt) override;

private:
	float m_speed = 175.0f;
	float m_brake_speed = 4.0f;
};