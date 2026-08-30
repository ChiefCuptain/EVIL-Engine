#include "pch.h"
#include "Framework/Game.h"

#include "Framework/Scene.h"

namespace nu
{
	void Game::Update(float dt)
	{
		m_scene->Update(dt);
	}

	void Game::Draw(const Renderer& renderer)
	{
		m_scene->Draw(renderer);
	}
}