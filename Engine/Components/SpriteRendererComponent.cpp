#include "pch.h"
#include "SpriteRendererComponent.h"
#include "Renderer.h"
#include "Actor.h"
#include "ResourceManager.h"
#include "Engine.h"

#include <string>

namespace nu
{
	FACTORY_REGISTER(SpriteRendererComponent);

	void SpriteRendererComponent::Draw(const Renderer& r) const
	{
		if(m_texture) r.DrawTexture(*m_texture, GetOwner()->GetTransform());
	}

	void SpriteRendererComponent::Read(const json::value_t& value)
	{
		RendererComponent::Read(value);

		std::string textureName;
		JSON_READ_NAME(value, "texture", textureName);
		if (!textureName.empty())
		{
			m_texture = Resources().Get<Texture>(textureName, Engine::Get().GetRenderer());
		}
	}
}