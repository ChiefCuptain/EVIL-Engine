#include "pch.h"

#include "Scene.h"
#include "Actor.h"
#include "Factory.h"
#include "Components/ColliderComponent.h"

namespace nu
{
	
	bool Scene::Load(const std::string& sceneName)
	{
		json::document_t document;
		if (json::Load(sceneName, document))
		{
			if (JSON_HAS_NAME(document, "actors"))
			{
				for (auto& actorValue : JSON_GET_NAME(document, "actors").GetArray())
				{
					std::string typeName;
					JSON_READ_NAME(actorValue, "type", typeName);

					auto actor = Factory::Instance().Create<Actor>(typeName);
					actor->Read(actorValue);

					bool prototype = false;
					JSON_READ(actorValue, prototype);

					if (prototype)
					{
						std::string name;
						JSON_READ(actorValue, name);
						Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
					}
					else
					{
						AddActor(std::move(actor));
					}
				}
			}
		}
		else
		{
			return false;
		}

		return true;
	}

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

				auto colliderA = actorA->GetComponent<ColliderComponent>();
				auto colliderB = actorB->GetComponent<ColliderComponent>();

				if (!colliderA || !colliderB) continue;

				if (colliderA->CheckCollision(*colliderB))
				{
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	}
}