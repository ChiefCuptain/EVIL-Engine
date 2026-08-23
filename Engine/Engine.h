#pragma once

#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Transform.h"

#include "Actor.h"
#include "Scene.h"
#include "Texture.h"
#include "File.h"
#include "JSON.h"
#include "StringUtils.h"

#include "Factory.h"
#include "ResourceManager.h"

#include "Renderer.h"
#include "Text.h"
#include "Input.h"
#include "GameTime.h"
#include "Timer.h"
#include "MathUtil.h"
#include "ParticleSystem.h"
#include "Audio.h"
#include "Physics.h"

#include "Game.h"

#include <iostream>
#include <vector>
#include <string>

namespace nu
{
	class Engine
	{
	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Quit();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		GameTime& GetTime() { return m_time; }
		ParticleSystem& GetPS() { return m_particle_system; }
		Audio& GetAudio() { return m_audio; }
		Physics& GetPhysics() { return m_physics; }
		Engine(const Engine&) = delete;
		Engine& operator = (const Engine&) = delete;

	private:
		Engine() = default;
	private:
		Input m_input;
		Renderer m_renderer;
		Audio m_audio;
		Physics m_physics;
		GameTime m_time;
		ParticleSystem m_particle_system;
	};

}