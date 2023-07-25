
#pragma once
#include "GameStateBase.h"
#include "GameObject/TextureManager.h"
#include "Gameobject/MouseButton.h"
#include "GameObject/Text.h"
#include "Sound.h"
#include "GSMenu.h"

class GSPause : public GameStateBase {
public:
	GSPause();
	~GSPause();

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

	std::list<std::shared_ptr<MouseButton>>		m_listButton;

	std::shared_ptr<Sprite2D>				opt_bg, menu_opt;
	std::list<std::shared_ptr<MouseButton>>	opt_bt;
	std::shared_ptr<MouseButton>			button, sfx_on_bt, sfx_off_bt, music_on_bt, music_off_bt;
};
