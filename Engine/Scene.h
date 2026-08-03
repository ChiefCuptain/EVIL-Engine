#pragma once
#include "Actor.h"

#include <vector>
#include <string>
#include <memory>

namespace nu
{
	class Scene
	{
	public:
		Scene() = default;
		void AddActor(std::unique_ptr<Actor> actor);

		void Update(float dt);
		void Draw(const class Renderer& renderer);

		template<typename T>
		T* GetActorByName(const std::string& name);

		int GetActorCountByTag(const std::string& tag) const;

		void ClearActors() { m_pending_clear = true; }

	private:
		void UpdateCollisions();

	private:
		bool m_pending_clear = false;
		std::vector<std::unique_ptr<Actor>> m_actors;
		std::vector<std::unique_ptr<Actor>> m_pending_actors;
	};

	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : m_actors)
		{
			T* actorT = dynamic_cast<T*>(actor.get());
			if (actorT && actorT->m_name == name)
			{
				return actorT;
			}
		}
		
		return nullptr;
	}
}