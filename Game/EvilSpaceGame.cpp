#include "EvilSpaceGame.h"
#include "Scene.h"
#include "Player.h"
#include "Assets.h"
#include "Enemy.h"
#include "Random.h"
#include <iostream>
#include <string>
#include <memory>


bool nu::EvilSpaceGame::Initialize()
{
	Game::Initialize();

	m_scene = new nu::Scene();


	//m_font = nu::Resources().Get<nu::Font>("Assets/Fonts/Kubasta.ttf", 120.0f);
	//m_font->Load("Assets/Fonts/Kubasta.ttf", 120.0f);

	m_bigFont = nu::Resources().GetWithID<nu::Font>("bigFont", "Assets/Fonts/Kubasta.ttf", 120.0f);
	m_mediumFont = nu::Resources().GetWithID<nu::Font>("mediumFont", "Assets/Fonts/Kubasta.ttf", 60.0f);
	m_smallFont = nu::Resources().GetWithID<nu::Font>("smallFont", "Assets/Fonts/Kubasta.ttf", 36.0f);


	m_title_text_1 = new nu::Text(m_bigFont);
	m_title_text_1->Create(nu::Engine::Get().GetRenderer(),"EVIL", {1.0f, 0.0f, 0.0f});

	m_game_over_text_1 = new nu::Text(m_bigFont);
	m_game_over_text_1->Create(nu::Engine::Get().GetRenderer(), "you died bozo", { 0.3f, 0.0f, 0.0f });

	m_title_text_2 = new nu::Text(m_mediumFont);
	m_title_text_2->Create(nu::Engine::Get().GetRenderer(), "space game", { 1.0f, 1.0f, 1.0f });
	m_game_over_text_2 = new nu::Text(m_mediumFont);

	m_level_text = new nu::Text(m_smallFont);
	
	m_lives_text = new nu::Text(m_smallFont);

	nu::Resources().GetWithID<nu::Texture>("background", "Assets/Textures/spr_bg.png", nu::Engine::Get().GetRenderer());
	nu::Resources().GetWithID<nu::Texture>("explosion", "Assets/Textures/spr_explosion.png", nu::Engine::Get().GetRenderer());

	nu::Engine::Get().GetAudio().AddSound("player_shoot", "Assets/Audio/snd_player_shoot.wav");
	nu::Engine::Get().GetAudio().AddSound("enemy_shoot", "Assets/Audio/snd_enemy_shoot.wav");
	nu::Engine::Get().GetAudio().AddSound("explosion", "Assets/Audio/snd_explosion.wav");

	return true;
}

void nu::EvilSpaceGame::Update(float dt)
{
	switch (m_gamestate)
	{
	case EvilSpaceGame::GameState::Title:
		if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			m_gamestate = GameState::StartGame;
		}
		break;
	case EvilSpaceGame::GameState::StartGame:
		m_lives = 3;
		m_gamestate = GameState::StartLevel;

		m_lives_string = std::to_string(m_lives);
		m_lives_string.append(" Lives");

		m_lives_text = new nu::Text(m_smallFont);
		m_lives_text->Create(nu::Engine::Get().GetRenderer(), m_lives_string, { 1.0f, 1.0f, 1.0f });

		m_level = 1;
		break;
	case EvilSpaceGame::GameState::StartLevel:
		m_level_string = "Level ";
		m_level_string.append(std::to_string(m_level));
		m_level_text = new nu::Text(m_smallFont);
		m_level_text->Create(nu::Engine::Get().GetRenderer(), m_level_string, { 1.0f, 1.0f, 1.0f });


		std::cout << m_lives << std::endl;
		if (m_scene->GetActorCountByTag("Player") != 1)
		{
			SpawnPlayer();
		}
		m_scene->Update(dt);
		for (int i = 0; i < round(pow(2, 1 + (0.5 * (m_level - 1)))); i++)
		{
			SpawnEnemy();
		}
		m_gamestate = GameState::Game;
		break;
	case EvilSpaceGame::GameState::Game:
		m_scene->Update(dt);
		if (m_scene->GetActorCountByTag("Enemy") == 0)
		{
			m_level_timer = { 3.0f };
			m_gamestate = GameState::EndLevel;
		}
		else if (m_scene->GetActorCountByTag("Player") == 0)
		{
			m_level_timer = { 2.5f };
			m_gamestate = GameState::PlayerDeath;
		}
		break;
	case EvilSpaceGame::GameState::EndLevel:
		m_scene->Update(dt);
		if (!m_level_timer.IsElapsed())
		{
			m_level_timer.Decrement(dt);
		}
		else
		{
			m_level += 1;
			if (m_level % 5 == 0)
			{
				m_lives += 1;
			}
			m_lives_string = std::to_string(m_lives);
			m_lives_string.append(" Lives");

			m_lives_text = new nu::Text(m_smallFont);
			m_lives_text->Create(nu::Engine::Get().GetRenderer(), m_lives_string, { 1.0f, 1.0f, 1.0f });
			m_gamestate = GameState::StartLevel;
		}
		break;
	case EvilSpaceGame::GameState::PlayerDeath:
		if (!m_level_timer.IsElapsed())
		{
			m_scene->Update(dt);
			m_level_timer.Decrement(dt);
		}
		else
		{
			m_lives -= 1;
			m_lives_string = std::to_string(m_lives);
			m_lives_string.append(" Lives");

			m_lives_text = new nu::Text(m_smallFont);
			m_lives_text->Create(nu::Engine::Get().GetRenderer(), m_lives_string, { 1.0f, 1.0f, 1.0f });

			if (m_lives <= 0) 
			{
				m_level_timer = { 4.0f };
				std::string final_level = "(Level ";
				final_level.append(std::to_string(m_level)).append(")");
				m_game_over_text_2->Create(nu::Engine::Get().GetRenderer(), final_level, { 0.7f, 0.7f, 0.7f });
				m_gamestate = GameState::GameOver;
			}
			else
			{
				m_scene->ClearActors();
				SpawnPlayer();
				m_scene->Update(dt);
			
				m_gamestate = GameState::StartLevel;
			}

		}
		break;
	case EvilSpaceGame::GameState::GameOver:

		if (!m_level_timer.IsElapsed())
		{
			m_scene->Update(dt);
			m_level_timer.Decrement(dt);
		}
		else
		{
			m_scene->ClearActors();
			m_scene->Update(dt);

			m_gamestate = GameState::Title;
		}
		break;
	default:
		break;
	}
}

void nu::EvilSpaceGame::Draw(const nu::Renderer& renderer)
{
	switch (m_gamestate)
	{
	case EvilSpaceGame::GameState::Title:
		m_title_text_1->Draw(
			nu::Engine::Get().GetRenderer(),
			nu::Engine::Get().GetRenderer().GetWindowWidth() / 2.0f,
			(nu::Engine::Get().GetRenderer().GetWindowHeight() / 2.0f) - 120.0f);
		m_title_text_2->Draw(
			nu::Engine::Get().GetRenderer(),
			nu::Engine::Get().GetRenderer().GetWindowWidth() / 2.0f,
			nu::Engine::Get().GetRenderer().GetWindowHeight() / 2.0f);
		break;
	case EvilSpaceGame::GameState::StartGame:
		break;
	case EvilSpaceGame::GameState::StartLevel:
		break;
	case EvilSpaceGame::GameState::Game:
		nu::Engine::Get().GetRenderer().DrawTexture(*nu::Resources().GetWithID<nu::Texture>("background", "Assets/Textures/spr_bg.png", nu::Engine::Get().GetRenderer()), 0.0f, 0.0f);
		m_level_text->Draw(
			nu::Engine::Get().GetRenderer(),
			30.0f, 15.0f, false);
		m_lives_text->Draw(
			nu::Engine::Get().GetRenderer(),
			30.0f, 60.0f, false);
		m_scene->Draw(renderer);
		break;
	case EvilSpaceGame::GameState::EndLevel:
		nu::Engine::Get().GetRenderer().DrawTexture(*nu::Resources().GetWithID<nu::Texture>("background", "Assets/Textures/spr_bg.png", nu::Engine::Get().GetRenderer()), 0.0f, 0.0f);
		m_level_text->Draw(
			nu::Engine::Get().GetRenderer(),
			30.0f, 15.0f, false);
		m_lives_text->Draw(
			nu::Engine::Get().GetRenderer(),
			30.0f, 60.0f, false);
		m_scene->Draw(renderer);
		break;
	case EvilSpaceGame::GameState::PlayerDeath:
		nu::Engine::Get().GetRenderer().DrawTexture(*nu::Resources().GetWithID<nu::Texture>("background", "Assets/Textures/spr_bg.png", nu::Engine::Get().GetRenderer()), 0.0f, 0.0f);
		m_level_text->Draw(
			nu::Engine::Get().GetRenderer(),
			30.0f, 15.0f, false);
		m_lives_text->Draw(
			nu::Engine::Get().GetRenderer(),
			30.0f, 60.0f, false);
		m_scene->Draw(renderer);
		break;
	case EvilSpaceGame::GameState::GameOver:
		m_game_over_text_1->Draw(
			nu::Engine::Get().GetRenderer(),
			nu::Engine::Get().GetRenderer().GetWindowWidth() / 2.0f,
			nu::Engine::Get().GetRenderer().GetWindowHeight() / 2.0f);
		m_game_over_text_2->Draw(
			nu::Engine::Get().GetRenderer(),
			nu::Engine::Get().GetRenderer().GetWindowWidth() / 2.0f,
			nu::Engine::Get().GetRenderer().GetWindowHeight() / 2.0f + 100.0f);
		break;
	default:
		break;
	}
}

void nu::EvilSpaceGame::SpawnPlayer()
{
	PlayerDesc playerDesc;
	playerDesc.name = "Player";
	playerDesc.tag = "Player";
	//playerDesc.model = assets::playerModel;
	playerDesc.texture = nu::Resources().Get<nu::Texture>("Assets/Textures/spr_player.png", nu::Engine::Get().GetRenderer());
	playerDesc.velocity = nu::Vector2{ 0.0f };
	playerDesc.transform = nu::Transform{ nu::Vector2{960.0f, 540.0f}, 0.0f, 1.5f };
	playerDesc.speed = 175.0f;

	std::unique_ptr<Player> player = std::make_unique<Player>(playerDesc);
	m_scene->AddActor(std::move(player));
}

void nu::EvilSpaceGame::SpawnEnemy()
{
	EnemyDesc enemyDesc;
	enemyDesc.name = "Enemy";
	enemyDesc.tag = "Enemy";
	//enemyDesc.model = assets::playerModel;
	enemyDesc.texture = nu::Resources().Get<nu::Texture>("Assets/Textures/spr_enemy.png", nu::Engine::Get().GetRenderer());
	enemyDesc.velocity = nu::Vector2{ 0.0f };
	enemyDesc.fire_cooldown = 3.5f;
	enemyDesc.speed = 125.0f;
	nu::Vector2 enemyPosition{ 0.0f };

	nu::Vector2 playerPosition{ m_scene->GetActorByName<Player>("Player")->GetTransform().position };

	do 
	{
		enemyPosition.x = nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWindowWidth());
		enemyPosition.y = nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWindowHeight());
	} while ((playerPosition - enemyPosition).Length() <= 500);
	

	enemyDesc.transform = nu::Transform{ enemyPosition, 0.0f, 0.75f };
	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(enemyDesc);
	m_scene->AddActor(std::move(enemy));
}
