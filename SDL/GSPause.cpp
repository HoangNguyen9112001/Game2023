#include "GSPause.h"
#include "GameObject/TextureManager.h"
#include "GameObject/MouseButton.h"
#include "GSMenu.h"
#include "SpriteAnimation.h"
#include "Math.h"
#include "SDL_mixer.h"

extern bool isPlayingSound;

GSPause::GSPause()
{

}
GSPause::~GSPause()
{}
void GSPause::Init()
{

	//background
	auto texture = ResourceManagers::GetInstance()->GetTexture("brick-bgr.png");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	//Boder
	m_boder = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("menu_opt.png"), SDL_FLIP_NONE);
	m_boder->SetSize(800, 300);
	m_boder->Set2DPosition((SCREEN_WIDTH - m_boder->GetWidth()) / 2, (SCREEN_HEIGHT - m_boder->GetHeight()) / 2);

	//continue
	std::shared_ptr<MouseButton> button = std::make_shared<MouseButton>(ResourceManagers::
		GetInstance()->GetTexture("button/032.png"), SDL_FLIP_HORIZONTAL);
	button->SetSize(70, 70);
	button->Set2DPosition(m_boder->Get2DPosition().x + 190, m_boder->Get2DPosition().y + 120);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	//Sound control
	m_soundButtonPlay = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("btn_music.tga"), SDL_FLIP_NONE);
	m_soundButtonPlay->SetSize(70, 70);
	m_soundButtonPlay->Set2DPosition(m_boder->Get2DPosition().x + 565, m_boder->Get2DPosition().y + 120);

	m_soundButtonPlay->SetOnClick([this]() {
		Mix_PauseMusic();
		GSPause::SetisPlayingSound(false);
		});

	m_listButton.push_back(m_soundButtonPlay);
	m_soundButtonOff = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("btn_music_off.tga"), SDL_FLIP_NONE);
	m_soundButtonOff->SetSize(70, 70);
	m_soundButtonOff->Set2DPosition(m_boder->Get2DPosition().x + 565, m_boder->Get2DPosition().y + 120);

	m_soundButtonOff->SetOnClick([this]() {
		Mix_ResumeMusic();
		GSPause::SetisPlayingSound(true);
		});
	m_listButton.push_back(m_soundButtonOff);

	//Restart
	button = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("btn_restart.tga"), SDL_FLIP_NONE);
	button->SetSize(70, 70);
	button->Set2DPosition(m_boder->Get2DPosition().x + 375, m_boder->Get2DPosition().y + 120);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		//GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);

	//title
	color = { 255, 255, 204 };
	m_textGameSetting = std::make_shared<Text>("Data/font2.ttf", color, 28);
	m_textGameSetting->SetSize(300, 70);
	m_textGameSetting->Set2DPosition((SCREEN_WIDTH - m_textGameSetting->GetWidth()) / 2, m_boder->Get2DPosition().y - 100);
	m_textGameSetting->LoadFromRenderText("Pause");

	m_KeyPress = 0;
	
}
void	GSPause::Exit()
{

}
void	GSPause::Pause()
{

}
void	GSPause::Resume()
{
}
void	GSPause::HandleEvents()
{
}
void	GSPause::HandleKeyEvents(SDL_Event& e)
{
}
void	GSPause::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
		if (GetisPlayingSound())
		{
			m_soundButtonPlay->HandleTouchEvent(&e);
		}
		else
		{
			m_soundButtonOff->HandleTouchEvent(&e);
		}
	}
}
void	GSPause::HandleMouseMoveEvents(int x, int y)
{
}
void	GSPause::Update(float deltaTime)
{
	m_soundButtonOff->Update(deltaTime);
	m_soundButtonPlay->Update(deltaTime);
	
}
void	GSPause::Draw(SDL_Renderer* renderer)
{

	m_background->Draw(renderer);
	m_boder->Draw(renderer);

	for (auto& it : m_listButton)
	{
		it->Draw(renderer);
	}

	if (GetisPlayingSound())
	{
		m_soundButtonPlay->Draw(renderer);
	}
	else
	{
		m_soundButtonOff->Draw(renderer);
	}
	m_textGameSetting->Draw(renderer);
}

void GSPause::SetisPlayingSound(bool isPlaying)
{
	isPlayingSound = isPlaying;
}

bool GSPause::GetisPlayingSound()
{
	return isPlayingSound;
}
