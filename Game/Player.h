#pragma once

#include "Actor.h"
#include <JSON.h>

struct PlayerDesc : public nu::ActorDesc
{
	float speed = 0.0f;
};

class Player : public nu::Actor
{
public:
	Player() = default;
	Player(const PlayerDesc& playerDesc) :
		Actor{ playerDesc },
		m_speed{ playerDesc.speed}
	{ }

	void Update(float dt) override;

	void OnCollision(Actor* other) override;

	float GetSpeed() const { return m_speed; }
	float GetBrakeSpeed() const { return m_brake_speed; }

	void Read(const nu::json::value_t& value) override;


private:
	float m_speed = 175.0f;
	float m_brake_speed = 4.0f;
	bool m_mouse_drag = false;
};