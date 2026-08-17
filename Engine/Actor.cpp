#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtil.h"
#include "Texture.h"
#include "Factory.h"



namespace nu {

    FACTORY_REGISTER(Actor);

    void Actor::Update(float dt)
    {
        // Lifespawn

        if (m_lifespan != -1.0f)
        {
            m_lifespan -= dt;
            m_destroyed = (m_lifespan <= 0.0f);
        }

        for (auto& component : m_components)
        {
            component->Update(dt);
        }

        m_transform.position += (m_velocity * dt);

        m_transform.position.x = Clamp(0.0f, 1920.0f, m_transform.position.x);
        m_transform.position.y = Clamp(0.0f, 1080.0f, m_transform.position.y);
    }

    void nu::Actor::Draw(const Renderer& r) const
    {
       /* for (auto& component : m_components)
        {
            component->Draw(r);
        }*/

        if (m_texture)
        {
            r.DrawTexture(*m_texture, m_transform);
        }
        if (m_model)
        {
            r.DrawModel(*m_model, m_transform);
        }
    }

    float Actor::GetRadius() const
    {
 


        if (m_model)
        {
            return m_model->GetRadius() * m_transform.scale * 0.9f;
        }
        if (m_texture)
        {
            return (m_texture->GetSize().Length()) * 0.5f * 0.9f;
        }
        return 0.0f;
    }

    void Actor::Read(const json::value_t& value)
    {
        Object::Read(value);
        JSON_READ_NAME(value, "tag", m_tag);
        if (JSON_HAS(value, "transform")) m_transform.Read(JSON_GET_NAME(value, "transform"));
        JSON_READ_NAME(value, "velocity", m_velocity);
        JSON_READ_NAME(value, "lifespan", m_lifespan);

    }
}