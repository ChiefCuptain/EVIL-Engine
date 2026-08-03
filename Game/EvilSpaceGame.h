#pragma once
#include "Game.h"

class Scene;

class EvilSpaceGame : public nu::Game
{
public:
	enum class GameState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		EndLevel,
		PlayerDeath,
		GameOver
	};
public:
	EvilSpaceGame() = default;
	EvilSpaceGame(nu::Scene* scene) :
		Game{ scene }
	{}

	bool Initialize() override;

	void Update(float dt) override;

	void Draw(const nu::Renderer& renderer) override;

	void SpawnPlayer();
	
	void SpawnEnemy();




private:
	int m_score = 0;
	int m_level = 0;
	int m_lives = 3;

	GameState m_gamestate = EvilSpaceGame::GameState::Title;
	nu::Timer m_level_timer = -1.0f;
	nu::Font* m_font = nullptr;
	nu::Text* m_title_text_1 = nullptr;
	nu::Text* m_title_text_2 = nullptr;
	nu::Text* m_level_text = nullptr;
	nu::Text* m_lives_text = nullptr;
	nu::Text* m_game_over_text_1 = nullptr;
	nu::Text* m_game_over_text_2 = nullptr;


	std::string m_level_string = "";
	std::string m_lives_string = "";

	

};