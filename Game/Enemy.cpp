#include "pch.h"
#include "Enemy.h"
#include "Player.h"
#include "Renderer.h"
#include "MathUtil.h"
#include "Engine.h"
#include "Bullet.h"
#include "Assets.h"

#include <cmath>
#include <ResourceManager.h>

FACTORY_REGISTER(Enemy);

void Enemy::Update(float dt)
{
    m_fire_timer += dt;

    Player* player = m_scene->GetActorByName<Player>("PlayerPrototype");
    if (player)
    {
        nu::Vector2 direction = player->GetTransform().position - m_transform.position;
        float rotation = direction.Angle();
        SetRotation(rotation * nu::RadToDeg);
        nu::Vector2 forward{ 1, 0 };
        forward = forward.Rotate(m_transform.rotation * nu::DegToRad);
        AddVelocity(forward * m_speed * dt);

        if ((m_velocity.x > 0 && GetTransform().position.x > player->GetTransform().position.x) || (m_velocity.x < 0 && GetTransform().position.x < player->GetTransform().position.x))
        {
            m_velocity.x *= (1.0f / (1.0f + m_brake_speed * dt));
        }
        if ((m_velocity.y > 0 && GetTransform().position.y > player->GetTransform().position.y) || (m_velocity.y < 0 && GetTransform().position.y < player->GetTransform().position.y))
        {
            m_velocity.y *= (1.0f / (1.0f + m_brake_speed * dt));
        }

        if (m_fire_timer > m_fire_cooldown)
        {
            m_fire_timer = 0.0f;

            auto actor = nu::Factory::Instance().Create<Bullet>("BulletPrototype");

            actor->SetTag("Enemy_Bullet");
            actor->SetTransform(m_transform);
            actor->SetScale(1.0f);
  
            m_scene->AddActor(std::move(actor));

            nu::Engine::Get().GetAudio().PlaySound("enemy_shoot");

        }

    } 



    Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other)
{
    if (other->GetTag() == "Player_Bullet")
    {
        for (int i = 0; i < 100; i++)
        {
            nu::Particle particle;
            particle.position = m_transform.position;
            particle.color = { 1.0f, 1.0f, 1.0f };
            particle.lifespan = nu::RandomFloat(0.5f, 2.0f);
            particle.velocity = { nu::RandomFloat(-600.0f, 600.0f), nu::RandomFloat(-600.0f, 600.0f) };

            nu::Engine::Get().GetPS().AddParticle(particle, nu::Resources().GetWithID<nu::Texture>("explosion", "Textures/spr_explosion.png", nu::Engine::Get().GetRenderer()));

        }
        nu::Engine::Get().GetAudio().PlaySound("explosion");
        SetDestroyed();
        other->SetDestroyed();
        
    }
}

void Enemy::Read(const nu::json::value_t& value)
{
    Actor::Read(value);

    JSON_READ_NAME(value, "fire_cooldown", m_fire_cooldown);
    JSON_READ_NAME(value, "speed", m_speed);
    JSON_READ_NAME(value, "brake_speed", m_brake_speed);
}

