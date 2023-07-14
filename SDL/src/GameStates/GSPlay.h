#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
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
	int m_KeyPress;
	void	AutoMove(std::shared_ptr<SpriteAnimation> obj);
	int m_enemySpeed;
	int main_heal = 100, e_heal = 50;
private:
	std::shared_ptr<Sprite2D>	m_background;
	//std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation, m_listEnemies;
	std::shared_ptr<SpriteAnimation> obj, enemy;
	std::shared_ptr<MouseButton> button;

//	EnemyWaveSpawner waveSpawner;
	float time = 0.0f;
	float m_Velocity = 10.0f;
};

