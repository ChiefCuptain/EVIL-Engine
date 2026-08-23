#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtil.h"
#include "Texture.h"
#include "Factory.h"
#include "ResourceManager.h"
#include "Components/RendererComponent.h"


namespace nu {

    FACTORY_REGISTER(Actor);

    Actor::Actor(const Actor& other) :
        Object{other},
        m_tag{other.m_tag},
        m_transform{other.m_transform},
        m_velocity{other.m_velocity}
    {
        for (const auto& component : other.m_components)
        {
            auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
            AddComponent(std::move(clone));
        }
    }

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
        for (auto& component : m_components)
        {
            auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
            if (rendererComponent)
            {
                rendererComponent->Draw(r);
            }
        }

    }

    float Actor::GetRadius() const
    {
        /*if (m_model)
        {
            return m_model->GetRadius() * m_transform.scale * 0.9f;
        }
        if (m_texture)
        {
            return (m_texture->GetSize().Length()) * 0.5f * 0.9f;
        }*/
        return 0.0f;
    }

    void Actor::Read(const json::value_t& value)
    {
        Object::Read(value);

        JSON_READ_NAME(value, "tag", m_tag);
        JSON_READ_NAME(value, "velocity", m_velocity);
        if (JSON_HAS(value, "transform")) m_transform.Read(JSON_GET_NAME(value, "transform"));
        JSON_READ_NAME(value, "lifespan", m_lifespan);

        if (JSON_HAS_NAME(value, "components"))
        {
            for (auto& componentValue : JSON_GET_NAME(value, "components").GetArray())
            {
                std::string typeName;
                JSON_READ_NAME(componentValue, "type", typeName);

                std::cout << "Loading component type : " << typeName << "\n";

                auto component = Factory::Instance().Create<Component>(typeName);

                if (component)
                {
                    component->Read(componentValue);
                    AddComponent(std::move(component));
                }
            }
        }
    }

    void Actor::AddComponent(std::unique_ptr<Component> component)
    {
        component->SetOwner(this);
        m_components.push_back(std::move(component));
    }
}