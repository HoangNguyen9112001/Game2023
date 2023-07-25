#include "GSPickPlayer.h"

int i = 0;

GSPickPlayer::GSPickPlayer()
{
}

GSPickPlayer::~GSPickPlayer()
{
}

void GSPickPlayer::Init()
{
	//backgr
	m_background = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("bg_city.png"), SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	//border1
	border1 = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("khung.png"), SDL_FLIP_NONE);
	border1->Set2DPosition(0, 80);
	border1->SetSize(SCREEN_WIDTH / 2, 500);
	border1->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		i = 0;
		});
	m_listButtons.push_back(border1);
	//border2
	border2 = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("khung.png"), SDL_FLIP_NONE);
	border2->Set2DPosition(SCREEN_WIDTH / 2, 80);
	border2->SetSize(SCREEN_WIDTH / 2, 500);
	border2->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		i = 1;
		});
	m_listButtons.push_back(border2);
	//player1
	player1 = std::make_shared<SpriteAnimation>(ResourceManagers::GetInstance()->GetTexture("player.png"), 1, 24, 8, 0.2f);
	player1->SetFlip(SDL_FLIP_NONE);
	player1->SetSize(120, 160);
	player1->Set2DPosition(border1->Get2DPosition().x + (border1->GetWidth() - player1->GetWidth()) / 2,
							border1->Get2DPosition().y + (border1->GetHeight() - player1->GetHeight()) / 2);
	//player2
	player2 = std::make_shared<SpriteAnimation>(ResourceManagers::GetInstance()->GetTexture("player2.tga"), 1, 2, 8, 0.9f);
	player2->SetFlip(SDL_FLIP_NONE);
	player2->SetSize(120, 160);
	player2->Set2DPosition(border2->Get2DPosition().x + (border2->GetWidth() - player2->GetWidth()) / 2,
							border2->Get2DPosition().y + (border2->GetHeight() - player2->GetHeight()) / 2);
	//back to menu
	std::shared_ptr<MouseButton> button = std::make_shared<MouseButton>(ResourceManagers::
											GetInstance()->GetTexture("button/021.png"), SDL_FLIP_NONE);
	button->SetSize(70, 70);
	button->Set2DPosition(75, 20);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButtons.push_back(button);
	

}

void GSPickPlayer::Exit()
{
}

void GSPickPlayer::Pause()
{
}

void GSPickPlayer::Resume()
{
}

void GSPickPlayer::HandleEvents()
{
}

void GSPickPlayer::HandleKeyEvents(SDL_Event& e)
{
}

void GSPickPlayer::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButtons)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}

}

void GSPickPlayer::HandleMouseMoveEvents(int x, int y)
{
}

void GSPickPlayer::Update(float deltaTime)
{
	for (auto& it : m_listButtons)
	{
		it->Update(deltaTime);
	}
	player1->Update(deltaTime);
	player2->Update(deltaTime);
	border1->Update(deltaTime);
	border2->Update(deltaTime);
}

void GSPickPlayer::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto& it : m_listButtons)
	{
		it->Draw(renderer);
	}
	player1->Draw(renderer);
	player2->Draw(renderer);
	border1->Draw(renderer);
	border2->Draw(renderer);
}
