#include "GSPauseGame.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Sprite2D.h"
#include "Text.h"
#include "MouseButton.h"
#include "SpriteAnimation.h"
#include "Math.h"

//control sound

extern int isPlayingSound;


GSPauseGame::GSPauseGame()
{
	m_KeyPress = 0;
}

GSPauseGame::~GSPauseGame()
{
}

void GSPauseGame::Init()
{
	//background
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_city.png");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	//back 
	std::shared_ptr<MouseButton> button = std::make_shared<MouseButton>(ResourceManagers::
		GetInstance()->GetTexture("btn_prev.tga"), SDL_FLIP_NONE);
	button->SetSize(60, 60);
	button->Set2DPosition(75, 20);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	m_soundButtonPlay = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("btn_music.tga"), SDL_FLIP_NONE);
	m_soundButtonPlay->SetSize(70, 70);
	m_soundButtonPlay->Set2DPosition(SCREEN_WIDTH - 450.0f, 200.0f);
	m_soundButtonPlay->SetOnClick([this]() {
		isPlayingSound = 0;
	//	ResourceManagers::GetInstance()->StopSound(SoundPlay);
		});
	m_listButton.push_back(m_soundButtonPlay);

	m_soundButtonOff = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("btn_music_off.tga"), SDL_FLIP_NONE);
	m_soundButtonOff->SetSize(70, 70);
	m_soundButtonOff->Set2DPosition(SCREEN_WIDTH - 450.0f, 200.0f);
	m_soundButtonOff->SetOnClick([this]() {
		isPlayingSound = 1;
	//	ResourceManagers::GetInstance()->PlaySound(SoundPlay, 1);
		});
	m_listButton.push_back(m_soundButtonOff);

	//Restart
	button = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("btn_restart.tga"), SDL_FLIP_NONE);
	button->Set2DPosition(SCREEN_WIDTH - 530.0f, 400.0f);
	button->SetSize(100, 100);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);
	//title
	color = { 0, 0, 0 };
	m_textGameSetting = std::make_shared<Text>("Data/font2.ttf", color, 28);
	m_textGameSetting->SetSize(500, 100);
	m_textGameSetting->Set2DPosition((SCREEN_WIDTH - m_textGameSetting->GetWidth()) / 2, SCREEN_HEIGHT / 2 - 300);
	m_textGameSetting->LoadFromRenderText("Pause");

	//Music title
	m_textGameVolumn = std::make_shared<Text>("Data/font2.ttf", color, 20);
	m_textGameVolumn->SetSize(500, 100);
	m_textGameVolumn->Set2DPosition(500.0f, 280.0f);
	m_textGameVolumn->LoadFromRenderText("Music");

	m_KeyPress = 0;
}

void GSPauseGame::Exit()
{
}

void GSPauseGame::Pause()
{
}

void GSPauseGame::Resume()
{
}

void GSPauseGame::HandleEvents()
{
}

void GSPauseGame::HandleKeyEvents(SDL_Event& e)
{
}

void GSPauseGame::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto& button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}

		if (isPlayingSound == 1)
		{
			m_soundButtonPlay->HandleTouchEvent(&e);
		}
		else
		{
			m_soundButtonOff->HandleTouchEvent(&e);
		}

	}
}

void GSPauseGame::HandleMouseMoveEvents(int x, int y)
{
}

void GSPauseGame::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto &it : m_listButton)
	{
		it->Update(deltaTime);
	}


	m_soundButtonPlay->Update(deltaTime);
	m_soundButtonOff->Update(deltaTime);
}

void GSPauseGame::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto& it : m_listButton)
	{
		it->Draw(renderer);
	}

	if (isPlayingSound == 1)
	{
		m_soundButtonPlay->Draw(renderer);
	}
	else
	{
		m_soundButtonOff->Draw(renderer);
	}
	m_textGameSetting->Draw(renderer);
	m_textGameVolumn->Draw(renderer);
}

