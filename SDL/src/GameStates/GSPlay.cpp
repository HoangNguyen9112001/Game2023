#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "GSMenu.h"


// tính khoảng cách giữa hai điểm
float distance(float x1, float y1, float x2, float y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// check VAR
bool intersect(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
	return !(x1 > x2 + w2 || x1 + w1 < x2 || y1 > y2 + h2 || y1 + h1 < y2);
}
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
			enemy = std::make_shared<SpriteAnimation>(texture, 1, 24, 8, 0.2f);
			enemy->SetFlip(SDL_FLIP_HORIZONTAL);
			enemy->SetSize(40, 50);
			enemy->Set2DPosition(rand() % 500, rand() % 500);

			m_listEnemies.push_back(enemy);
		}
		for (auto enemy : m_listEnemies) {
			GSPlay::AutoMove(enemy);

			//check VAR
			if (intersect(obj->Get2DPosition().x, obj->Get2DPosition().y, obj->GetWidth(), obj->GetHeight(),
				enemy->Get2DPosition().x, enemy->Get2DPosition().y, enemy->GetWidth(), enemy->GetHeight())) {
				main_heal -= 50;
				e_heal -= 50;
			}

			//delete enemy
			if (e_heal <= 0) {
				enemy.reset();
				continue;
			}
			enemy->Update(deltaTime);
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
		for (auto it : m_listEnemies) {
			it->Draw(renderer);
		}
	
}

void GSPlay::AutoMove(std::shared_ptr<SpriteAnimation> e) {

	m_enemySpeed = rand() % 3 + 1;
	//tinh go'c giua enemy vs palyer
	float angle = atan2(obj->Get2DPosition().y - e->Get2DPosition().y, obj->Get2DPosition().x - e->Get2DPosition().x);
	//tinh khoang cach
	float dist = distance(obj->Get2DPosition().x, obj->Get2DPosition().y, e->Get2DPosition().x, e->Get2DPosition().y);

	if (dist > 10)
	{
		float a = e->Get2DPosition().x;
		a += cos(angle) * m_enemySpeed;
		float b = e->Get2DPosition().y;
		b += sin(angle) * m_enemySpeed;

		e->Set2DPosition(a, b);
		dist = distance(obj->Get2DPosition().x, obj->Get2DPosition().y, a, b);
	}
	
}