#include "pch.h"

#include "Scene.h"
#include "Actor.h"

namespace nu
{
	void Scene::AddActor(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_pending_actors.push_back(std::move(actor)); 
	}

	void Scene::Update(float dt)
	{
		for (auto& actor : m_actors)
		{
			actor->Update(dt);
		}

		UpdateCollisions();

		// Remove destroyed actors
		std::erase_if(m_actors, [](auto& actor) {return actor->m_destroyed; });
		

		for (auto& actor : m_pending_actors) {
			m_actors.push_back(std::move(actor));
		}
		m_pending_actors.clear();

		if (m_pending_clear)
		{
			m_pending_clear = false;
			m_actors.clear();
		}
	}
	void Scene::Draw(const Renderer& renderer)
	{
		for (const auto& actor : m_actors)
		{
			actor->Draw(renderer);
		}
	}

	int Scene::GetActorCountByTag(const std::string& tag) const
	{
		int count = 0;
		for (const auto& actor : m_actors)
		{
			if (actor->GetTag() == tag) count += 1;
		}
		return count;
	}

	void Scene::UpdateCollisions()
	{
		for (auto& actorA : m_actors)
		{
			for (auto& actorB : m_actors)
			{
				if (actorA == actorB || actorA->GetDestroyed() || actorB->GetDestroyed()) continue;

				float distance = (actorA->m_transform.position - actorB->m_transform.position).Length();

				if (distance <= actorA->GetRadius() + actorB->GetRadius())
				{
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	}
}