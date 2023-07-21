#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include"GameObject/Text.h"
#include"Timer.h"
//#include "../EnemyWaveSpawner.h"
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
	void	Draw(SDL_Renderer* renderer) override;
	void	EnemyAutoMove(std::shared_ptr<SpriteAnimation> obj);

	int m_enemySpeed;

	int playerDirection = -1;
	double weaponAngle = 0;
	int m_KeyPress;
	int m_bullet_speed = 20;
	int m_MouseMotion;
	int characterDirection;
	int bullet_offset_x = 30;
	int bullet_offset_y = 28;

private:
	double scores, golds;

	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Sprite2D>	gold;
	std::shared_ptr<Sprite2D>	weapon;
	std::shared_ptr<Sprite2D>	bullet;

	std::shared_ptr<Text>		m_score;
	std::shared_ptr<Text>		score;
	std::shared_ptr<Text>		money;


	SDL_Color m_textColor;

	std::list<std::shared_ptr<Sprite2D>>		m_listBullets;
	std::list<std::shared_ptr<MouseButton>>		m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listEnemies;

	std::shared_ptr<SpriteAnimation>			player;
	std::shared_ptr<SpriteAnimation>			enemy;

	std::shared_ptr<MouseButton>				button;

	float time = 0.0f;
	float m_Velocity = 10.0f;

};

