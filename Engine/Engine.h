#pragma once

#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Transform.h"

#include "Actor.h"
#include "Scene.h"

#include "Renderer.h"
#include "Text.h"
#include "Input.h"
#include "GameTime.h"
#include "Timer.h"
#include "MathUtil.h"
#include "ParticleSystem.h"

#include "Game.h"

#include "fmod.hpp"

#include <iostream>
#include <vector>
#include <string>
#include "Audio.h"

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

	private:
		Engine() = default;
	private:
		Input m_input;
		Renderer m_renderer;
		Audio m_audio;
		
		GameTime m_time;
		ParticleSystem m_particle_system;
	};

}