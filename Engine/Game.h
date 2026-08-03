#pragma once
#include "Engine.h"

namespace nu
{
	class Scene;

	class Game
	{
	public:
		Game() = default;
		Game(Scene* scene) : m_scene{scene} {}

		virtual bool Initialize() { return true; }
		virtual void Quit() {}

		virtual void Update(float dt);
		virtual void Draw(const class Renderer& renderer);

		void SetScene(Scene* scene) { m_scene = scene; }


	protected:
		Scene* m_scene = nullptr;
	};
}