#include "pch.h"
#include "Player.h"
#include "Renderer.h"
#include "MathUtil.h"
#include "Engine.h"
#include "Assets.h"
#include "Bullet.h"

void Player::Update(float dt)
{
    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_T))
    {
        m_mouse_drag = !m_mouse_drag;
    }

    if (m_mouse_drag) 
    {
        SetPosition(nu::Engine::Get().GetInput().GetMousePosition());
    }
    else 
    {
        //nu::Vector2 force{ 0, 0 };
        float thrust = 0.0f;

        if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = m_speed;
        if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

        float rotate = 0.0f;

        if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
        if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = 180.0f;

        if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_LSHIFT))
        {
            thrust *= 2.0f;
            rotate *= 2.0f;
        }
        else if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_LCTRL))
        {
            thrust *= 0.5f;
            rotate *= 0.5f;
        }


        SetRotation(m_transform.rotation + rotate * dt);

        nu::Vector2 forward{ 1, 0 };

        nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * thrust;

        AddVelocity(velocity * dt);

        if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) SetVelocity(GetVelocity() * (1.0f / (1.0f + m_brake_speed * dt)));

        // Fire

        if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_E))
        {
            BulletDesc bulletDesc;
            bulletDesc.name = "Bullet";
            bulletDesc.tag = "Player_Bullet";
            bulletDesc.model = assets::bulletModel;
            bulletDesc.transform = m_transform;
            bulletDesc.transform.scale = 7.0f;
            bulletDesc.lifespan = 2.0f;
            bulletDesc.speed = 800.0f;

            std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(bulletDesc);
            m_scene->AddActor(std::move(bullet));

            nu::Engine::Get().GetAudio().PlaySound("player_shoot");
        }

        //SetVelocity(GetVelocity() + force * dt);
        //SetRotation(GetTransform().position.Normalized().Angle() * nu::RadToDeg);
    }
    
    Actor::Update(dt);
}

void Player::OnCollision(Actor* other)
{
    if (other->GetTag() == "Enemy_Bullet")
    {
        for (int i = 0; i < 100; i++)
        {
            nu::Particle particle;
            particle.position = m_transform.position;
            particle.color = { 1.0f, 1.0f, 1.0f };
            particle.lifespan = nu::RandomFloat(0.5f, 2.0f);
            particle.velocity = { nu::RandomFloat(-600.0f, 600.0f), nu::RandomFloat(-600.0f, 600.0f) };

            nu::Engine::Get().GetPS().AddParticle(particle);
        }
        nu::Engine::Get().GetAudio().PlaySound("explosion");
        SetDestroyed();
        other->SetDestroyed();
        
    }
}
