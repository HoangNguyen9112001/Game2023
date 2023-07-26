#include "GSEndGame.h"
#include "GameObject/TextureManager.h"
#include "GameObject/MouseButton.h"
#include "GSMenu.h"


GSEndGame::GSEndGame() : GameStateBase(StateType::STATE_ENDGAME), eg_bg(nullptr), eg_bt(std::list<std::shared_ptr<MouseButton>>{}) {

}
GSEndGame::~GSEndGame() {


}

void GSEndGame::Init() {
	//background
	eg_bg = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("bg_menu.tga"), SDL_FLIP_NONE);
	eg_bg->Set2DPosition(0, 0);
	eg_bg->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	//Button 
	button = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("button/006.png"), SDL_FLIP_NONE);
	button->SetSize(100, 100);
	button->Set2DPosition(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 50);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	eg_bt.push_back(button);
}

void GSEndGame::Exit()
{
}

void GSEndGame::Pause()
{
}

void GSEndGame::Resume()
{
}

void GSEndGame::HandleEvents()
{
}

void GSEndGame::HandleKeyEvents(SDL_Event& e)
{
}

void GSEndGame::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : eg_bt)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSEndGame::HandleMouseMoveEvents(int x, int y)
{
}

void GSEndGame::Update(float deltaTime)
{
}

void GSEndGame::Draw(SDL_Renderer* renderer)
{
	eg_bg->Draw(renderer);
	for (auto it : eg_bt)
	{
		it->Draw(renderer);
	}
	//menu_go->Draw(renderer);
}


