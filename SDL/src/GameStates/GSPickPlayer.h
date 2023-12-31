#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "SpriteAnimation.h"
#include "Sprite2D.h"
#include "TextureManager.h"

class GSPickPlayer : public GameStateBase
{
public:
	GSPickPlayer();
	~GSPickPlayer();

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
private:

	std::shared_ptr<Sprite2D>		m_background;

	std::shared_ptr<MouseButton>	border1;
	std::shared_ptr<MouseButton>	border2;

	std::list<std::shared_ptr<MouseButton>> m_listButtons;

	std::shared_ptr<SpriteAnimation> player1;
	std::shared_ptr<SpriteAnimation> player2;

};