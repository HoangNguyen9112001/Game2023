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
	int main_heal = 100, e_heal = 50;
	int playerDirection = -1;
	double weaponAngle = 0;
	int m_KeyPress;

private:
	std::string scores, golds;
	std::shared_ptr<Sprite2D>	m_background, gold, weapon;
	std::shared_ptr<Text>		m_score, score, money;
	SDL_Color m_textColor;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation, m_listEnemies;
	std::shared_ptr<SpriteAnimation> obj, enemy;
	std::shared_ptr<MouseButton> button;

	float time = 0.0f;
	float m_Velocity = 10.0f;

};

