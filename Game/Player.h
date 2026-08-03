#pragma once

#include "Actor.h"

struct PlayerDesc : public nu::ActorDesc
{
	float speed;
};

class Player : public nu::Actor
{
public:
	Player() = default;
	Player(const PlayerDesc& playerDesc) :
		Actor{ playerDesc },
		m_speed{ playerDesc.speed}
	{ }

	Player(const nu::Transform& transform) : Actor{ transform } {}
	Player(const nu::Transform& transform, const nu::Model& model) : Actor{ transform, model } {}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;

private:
	int m_ammo = 0;
	float m_speed = 175.0f;
	float m_brake_speed = 4.0f;
	bool m_mouse_drag = false;
};