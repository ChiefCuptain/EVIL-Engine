#include "DinkiverseSandbox.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include <iostream>
#include <string>
#include <memory>


bool nu::DinkiverseSandbox::Initialize()
{
	SetWorkingDirectory("DinkiverseSandbox");

	Game::Initialize();

	m_scene = std::make_unique<Scene>();
	//m_scene->Load("Data/scene.json");

	return true;
}

void nu::DinkiverseSandbox::Update(float dt)
{
	switch (m_gamestate)
	{
	}
}

void nu::DinkiverseSandbox::Draw(const nu::Renderer& renderer)
{
	switch (m_gamestate)
	{
	}
}

