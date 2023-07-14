#pragma once
#include "GameStateBase.h"
#include "GameObject/TextureManager.h"
#include "Gameobject/MouseButton.h"
#include "GameObject/Text.h"

class Credit : public GameStateBase{
public:
	Credit();
	~Credit();
	
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
	std::shared_ptr<Sprite2D>				cre_background;
	std::list<std::shared_ptr<MouseButton>>	cre_btn;
	std::shared_ptr<MouseButton>			button;
	std::shared_ptr<Text>					credit_text;
	SDL_Color cre_text_color;
	
};
