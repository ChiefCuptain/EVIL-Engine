#include "pch.h"
#include "SpriteAnimationRendererComponent.h"
#include "Core/Factory.h"
#include "Resources/ResourceManager.h"
#include "Renderer/TextureFrames.h"
#include "Engine.h"

namespace nu
{
	FACTORY_REGISTER(SpriteAnimationRendererComponent);

	void SpriteAnimationRendererComponent::Update(float dt)
	{
		m_frameTimer += dt;
		float frameTime = 1.0f / m_fps;

		while (m_frameTimer >= frameTime)
		{
			m_frame++;
			m_frame %= m_textureFrames->GetTotalFrames();

			m_frameTimer -= frameTime;
		}

	}

	void SpriteAnimationRendererComponent::Draw(const Renderer& r) const
	{
		if (!m_textureFrames) return;

		auto& transform = GetOwner()->GetTransform();
		r.DrawTexture(*m_textureFrames->GetTexture(), m_textureFrames->GetFrameRect(m_frame), transform);
	}

	void SpriteAnimationRendererComponent::Read(const json::value_t& value)
	{
		RendererComponent::Read(value);

		JSON_READ_NAME_REQ(value, "fps", m_fps);
		JSON_READ_NAME(value, "loop", m_loop);

		std::string texture_frames;
		JSON_READ_REQ(value, texture_frames);
		if (!texture_frames.empty())
		{
			m_textureFrames = Resources().Get<TextureFrames>(texture_frames, Engine::Get().GetRenderer());
			if (!m_textureFrames)
			{
				std::cerr << "Could not load TextureFrames : " << texture_frames << "\n";
			}
		}

	}
}
