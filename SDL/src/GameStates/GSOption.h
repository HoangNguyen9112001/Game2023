
#pragma once
#include "GameStateBase.h"
#include "GameObject/TextureManager.h"
#include "Gameobject/MouseButton.h"
#include "GameObject/Text.h"
#include "Sound.h"
#include "GSMenu.h"
#include "Text.h"
#include "GSPlay.h"
class GSOption : public GameStateBase {
public:
	GSOption();
	~GSOption();

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

	std::shared_ptr<Sprite2D>				opt_bg, m_high_score;
	std::shared_ptr<MouseButton>			button;
	std::shared_ptr<Text>					best_score;
	int HighScore;
};
