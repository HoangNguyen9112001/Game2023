#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include"GameObject/Text.h"
#include"Timer.h"
#include "Sound.h"

class Sprite2D;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	drawRect(SDL_Renderer* renderer);
	void	drawEnemyRect(SDL_Renderer* renderer);
	void	Draw(SDL_Renderer* renderer) override;
	void	EnemyAutoMove(std::shared_ptr<SpriteAnimation> obj);
	
	int		GetHighScore();
	int		bestScore = 0;
	//int		SetHighScore(int sc);
	int m_enemySpeed;

	int playerHealth = 3;
	int playerDirection = -1;
	double weaponAngle = 0;
	int m_KeyPress;

	Uint32 startTime = SDL_GetTicks();
	Uint32 currentTime, elapsedTime;
	int countdown = 0.25 * 60;

	int m_bullet_speed = 20;
	int m_MouseMotion;

	int m_lastShootTime;
	int m_shootDelay = 5;
	
	void UpdateValue(int& value, int upd);
private:
	int scores = 0;

	int m_textwidth = 20,
		m_textheight = 50;



	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Sprite2D>	m_gold;
	std::shared_ptr<Sprite2D>	weapon;
	std::shared_ptr<Sprite2D>	bullet;

	std::shared_ptr<Sound> BgSound;
	std::shared_ptr<Sound> Shooting;

	std::shared_ptr<Text>		m_score;
	std::shared_ptr<Text>		score;
	std::shared_ptr<Text>		gold;
	std::shared_ptr<Text>		min;
	std::shared_ptr<Text>		sec;
	std::shared_ptr<Sprite2D>	m_heartIcon;
	std::vector<std::shared_ptr<Sprite2D>> m_heartIcons;


	SDL_Color m_textColor;

	std::list<std::shared_ptr<Sprite2D>>		m_listBullets;
	std::list<std::shared_ptr<MouseButton>>		m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listEnemies;

	std::shared_ptr<SpriteAnimation>			player;
	std::shared_ptr<SpriteAnimation>			enemy;

	std::shared_ptr<MouseButton>				button;
	
	std::shared_ptr<Sprite2D>	m_victoryIcon;
	std::shared_ptr<MouseButton> m_nextButton;
	std::shared_ptr<MouseButton> m_endGameButton;


	float time = 0.0f;
	float m_Velocity = 10.0f;

};

