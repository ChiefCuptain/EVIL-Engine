#pragma once
#include "Framework/Game.h"
#include "Resources/ResourceManager.h"

class Scene;
namespace nu
{
	class DinkiverseSandbox : public Game
	{
	public:
		enum class GameState
		{
			Title,
		};
	public:
		DinkiverseSandbox() = default;

		bool Initialize() override;

		void Update(float dt) override;

		void Draw(const nu::Renderer& renderer) override;

	private:
		GameState m_gamestate = DinkiverseSandbox::GameState::Title;

	}; 
}