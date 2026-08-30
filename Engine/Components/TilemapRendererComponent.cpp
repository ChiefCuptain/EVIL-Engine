#include "pch.h"
#include "TilemapRendererComponent.h"
#include "Renderer/Tilemap.h"
#include "Engine.h"
#include "Physics/PhysicsBody.h"
namespace nu
{
	FACTORY_REGISTER(TileMapRendererComponent)

	TileMapRendererComponent::TileMapRendererComponent(const TileMapRendererComponent& other)
	{
		m_tilemapName = other.m_tilemapName;
	}

	void TileMapRendererComponent::Start()
	{
		m_tilemap = Resources().Get<Tilemap>(m_tilemapName, Engine::Get().GetRenderer());
	}

	void TileMapRendererComponent::Draw(const Renderer& r) const
	{

	}

	void TileMapRendererComponent::Read(const json::value_t& value)
	{
		RendererComponent::Read(value);
		
		JSON_READ_NAME_REQ(value, "tilemap_name", m_tilemapName);
	}
}