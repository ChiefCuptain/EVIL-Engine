#pragma once

#pragma once

#include "Actor.h"

struct EnemyDesc : public nu::ActorDesc
{
	float speed;
	float fire_cooldown;
};

class Enemy : public nu::Actor
{
public:
	Enemy() = default;
	Enemy(const EnemyDesc& enemyDesc) :
		Actor{ enemyDesc },
		m_speed{ enemyDesc.speed },
		m_fire_cooldown{ enemyDesc.fire_cooldown }
	{ }

	void Update(float dt) override;

	void OnCollision(Actor* other) override;

private:
	float m_fire_cooldown = 2.0f;
	float m_fire_timer = 0.0f;
	float m_speed = 175.0f;
	float m_brake_speed = 4.0f;
};