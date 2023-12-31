#include "GSMenu.h"

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}

bool isPlayingSound = true;

void GSMenu::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background.png");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	//Sound

	//auto m_Sound = std::make_shared<Sound>("Data/Sounds/Menu.mp3");
	//m_Sound->PlaySound();
	//m_Sound->LoadSound("Data/Sounds/Menu.mp3");

	auto m_Sound = std::make_shared<Sound>("Data/Sounds/MainBG.ogg");
	m_Sound->PlaySound();
	m_Sound->LoadSound("Data/Sounds/MainBG.ogg");


	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("BTN/Play_BTN.png");
	std::shared_ptr<MouseButton> btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnPlay->SetSize(150, 150);
	btnPlay->Set2DPosition((SCREEN_WIDTH - btnPlay->GetWidth())/2, (SCREEN_HEIGHT - btnPlay->GetHeight()) / 2);
	btnPlay->SetOnClick([this]() {
		Exit();
		//Pause();
		//auto m_Sound = std::make_shared<Sound>("Data/Sounds/BgSoundPlay.mp3");
		/*m_Sound->PlaySound();
		m_Sound->LoadSound("Data/Sounds/BgSoundPlay.mp3");*/	
		});
	m_listButton.push_back(btnPlay);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("BTN/Close_BTN.png");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(50, 50);
	btnClose->Set2DPosition(SCREEN_WIDTH - btnClose->GetWidth(), 10);
	btnClose->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(btnClose);

	//Setting game
	texture = ResourceManagers::GetInstance()->GetTexture("BTN/Rating_BTN.png");
	std::shared_ptr<MouseButton> btnOption = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnOption->SetSize(100, 100);
	btnOption->Set2DPosition((SCREEN_WIDTH - btnOption->GetWidth()) / 2, SCREEN_HEIGHT / 2 + 170);
	btnOption->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OPTION);
		});
	m_listButton.push_back(btnOption);

	//CREDIT game
	texture = ResourceManagers::GetInstance()->GetTexture("BTN/FAQ_BTN.png");
	btnCredit = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnCredit->Set2DPosition((SCREEN_WIDTH - btnCredit->GetWidth()) / 2, SCREEN_HEIGHT / 2 + 280);
	btnCredit->SetSize(100, 100);
	btnCredit->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_CREDIT);
		});
	m_listButton.push_back(btnCredit);

	// game title
	///Set Font
	m_textColor = { 0, 0, 0 };
	m_textGameName = std::make_shared<Text>("Data/MochiyPopOne.ttf", m_textColor, 28);
	m_textGameName->SetSize(500, 100);
	m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth())/2, SCREEN_HEIGHT / 2 - 300);
	m_textGameName->LoadFromRenderText("Monster Survivor");
	
}

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
	m_Sound->StopSound();
	GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PICKPLAYER);
}


void GSMenu::Pause()
{

	
	m_Sound->PauseSound();

	//m_Sound->StopSound();


}

void GSMenu::Resume()
{

	m_Sound->ResumeSound();

}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(SDL_Event& e)
{
}

void GSMenu::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button ->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}
float time = 0.0f;
void GSMenu::Update(float deltaTime)
{
	time += deltaTime;
	//printf("DeltaTime = %f", deltaTime);
	if (time >= 1.5f)
	{
		time = 0.0f;
	}
	m_background->Update(deltaTime);
	for (auto& it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw(SDL_Renderer* renderer)
{
	m_background->DrawOriginal(renderer);
	for (auto& it : m_listButton)
	{
		it->Draw(renderer);
	}
	m_textGameName->Draw(renderer);
}
