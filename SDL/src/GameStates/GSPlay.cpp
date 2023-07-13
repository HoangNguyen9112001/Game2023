#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "GSMenu.h"


GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}

//void GSPlay::Initializations()
//{
//	waveSpawner.Init();
//}

void GSPlay::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_city.png");

	// background
	
	m_background = std::make_shared<Sprite2D>( texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>( texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

   // Animation 
	texture = ResourceManagers::GetInstance()->GetTexture("player.png");
	obj = std::make_shared<SpriteAnimation>(texture, 1, 24, 8, 0.2f);
	obj->SetFlip(SDL_FLIP_HORIZONTAL);
	obj->SetSize(100, 100);
	obj->Set2DPosition(350, 400);

	m_listAnimation.push_back(obj);

	

	//for (int i = 0; i < 50; i++) {

	//	texture = ResourceManagers::GetInstance()->GetTexture("logo2.png");
	//	obj = std::make_shared<SpriteAnimation>(texture, 1, 24, 8, 0.2f);
	//	obj->SetFlip(SDL_FLIP_HORIZONTAL);
	//	obj->SetSize(40, 50);
	//	obj->Set2DPosition(rand() % 500, rand() % 500);

	//	m_listAnimation.push_back(obj);
	//}

	

	
	
	//Camera::GetInstance()->SetTarget(obj);
	

	m_KeyPress = 0;
}

void GSPlay::Exit()
{
	
}


void GSPlay::Pause()
{

}
void GSPlay::Resume()
{
	
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) //For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			m_KeyPress |= 1 << 3;
			break;
		case SDLK_DOWN:
			m_KeyPress |= 1 << 1;
			break;
		case SDLK_LEFT:
			m_KeyPress |= 1;
			break;
		case SDLK_RIGHT:
			m_KeyPress |= 1 << 2;
			break;
		default:
			break;
		}

	}
	//Key Up
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_KeyPress ^= 1;
			break;
		case SDLK_DOWN:
			m_KeyPress ^= 1 << 1;
			break;
		case SDLK_RIGHT:
			m_KeyPress ^= 1 << 2;
			break;
		case SDLK_UP:
			m_KeyPress ^= 1 << 3;
			break;
		default:
			break;
		}

	}
}

void GSPlay::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}


float time1 = 0.0f;
void GSPlay::Update(float deltaTime)
{
	switch (m_KeyPress)//Handle Key event
	{
	default:
		break;
	}
	
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation)
	{
		if (m_KeyPress == 1)
		{
			
			it->MoveLeft(deltaTime);
		}
		it->Update(deltaTime);
		if (m_KeyPress == 2)
		{
			
			it->MoveDown(deltaTime);
		}
		it->Update(deltaTime);
		if (m_KeyPress == 4)
		{

			it->MoveRight(deltaTime);
		}
		it->Update(deltaTime);
		if (m_KeyPress == 8)
		{

			it->MoveUp(deltaTime);
		}
		it->Update(deltaTime);

	}


	time1 += deltaTime;

	if (time1 >= 1.5f)
	{
		for (int i = 0; i < 1; i++) {

			auto texture = ResourceManagers::GetInstance()->GetTexture("player.png");
			obj = std::make_shared<SpriteAnimation>(texture, 1, 24, 8, 0.2f);
			obj->SetFlip(SDL_FLIP_HORIZONTAL);
			obj->SetSize(40, 50);
			obj->Set2DPosition(rand() % 500, rand() % 500);

			m_listAnimation.push_back(obj);
		}
	}
	//Update position of camera
	//Camera::GetInstance()->Update(deltaTime);
	//obj->Update(deltaTime);
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	//m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	//obj->Draw(renderer);
	
		for (auto it : m_listAnimation)
		{

			it->Draw(renderer);
	
		}
	
	
}