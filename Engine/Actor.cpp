#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtil.h"


namespace nu {

    void Actor::Update(float dt)
    {
        // Lifespawn

        if (m_lifespan != -1.0f)
        {
            m_lifespan -= dt;
            m_destroyed = (m_lifespan <= 0.0f);
        }

        m_transform.position += (m_velocity * dt);

        m_transform.position.x = Clamp(0.0f, 1920.0f, m_transform.position.x);
        m_transform.position.y = Clamp(0.0f, 1080.0f, m_transform.position.y);
    }

    void nu::Actor::Draw(const Renderer& r) const
    {
        r.DrawModel(m_model, m_transform);
        /*r.SetColor(255, 255, 127);
        r.RenderRect(
            m_transform.position.x - (m_transform.scale * 0.5f)
            , m_transform.position.y - (m_transform.scale * 0.5f)
            , m_transform.scale
            , m_transform.scale
            , true);*/
    }

    float Actor::GetRadius() const
    {
        return m_model.GetRadius() * m_transform.scale * 0.9f;
    }
}