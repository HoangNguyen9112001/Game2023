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

	//background
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_city.png");
	m_background = std::make_shared<Sprite2D>( texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// Close button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>( texture, SDL_FLIP_NONE);
	button->SetSize(60, 60);
	button->Set2DPosition(SCREEN_WIDTH - 75, 20);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// Pause button
	button = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("btn_pause.tga"), SDL_FLIP_NONE);
	button->SetSize(60, 60);
	button->Set2DPosition(SCREEN_WIDTH - 150, 20);
	button->SetOnClick([this]() {
		
		});
	m_listButton.push_back(button);

   // Player
	texture = ResourceManagers::GetInstance()->GetTexture("player.png");
	obj = std::make_shared<SpriteAnimation>(texture, 1, 24, 8, 0.2f);
	obj->SetFlip(SDL_FLIP_HORIZONTAL);
	obj->SetSize(100, 100);
	obj->Set2DPosition(350, 400);
	m_listAnimation.push_back(obj);

	//Weapon
	weapon = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("weaponR1.png"), playerDirection == 1 ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL);
	weapon->SetSize(30, 30);
	double handX = obj->Get2DPosition().x + obj->GetWidth() / 2 + cos(weaponAngle * M_PI / 180) * playerDirection * 25;
	double handY = obj->Get2DPosition().y + obj->GetHeight() / 2 + sin(weaponAngle * M_PI / 180) * 25;
	weapon->Set2DPosition(handX - weapon->GetWidth() / 2, handY - weapon->GetHeight() / 2);

	
	//SCORE
	scores = '0';
	m_textColor = { 0, 0, 255 };
	m_score = std::make_shared<Text>("Data/calibrili.ttf", m_textColor, 20);
	m_score->SetSize(75, 30);
	m_score->Set2DPosition((SCREEN_WIDTH - m_score->GetWidth()) / 3, 45);
	m_score->LoadFromRenderText("Score: ");
	
	score = std::make_shared<Text>("Data/calibrili.ttf", m_textColor, 20);
	score->SetSize(20, 50);
	score->Set2DPosition(m_score->Get2DPosition().x + m_score->GetWidth() + 5, 30);
	score->LoadFromRenderText(scores);

	//Bullet


	//gold
	golds = '0';
	gold = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("gold_icon.png"), SDL_FLIP_NONE);
	gold->SetSize(60, 60);
	gold->Set2DPosition(score->Get2DPosition().x + score->GetWidth() + 50, 20);

	money = std::make_shared<Text>("Data/calibrili.ttf", m_textColor, 20);
	money->SetSize(20, 50);
	money->Set2DPosition(gold->Get2DPosition().x + gold->GetWidth() + 10, 30);
	money->LoadFromRenderText(golds);

	//Guns shop
	button = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("guns_shop_icon.png"), SDL_FLIP_HORIZONTAL);
	button->SetSize(60, 60);
	button->Set2DPosition(SCREEN_WIDTH - 230, 20);
	button->SetOnClick([this]() {

		});
	m_listButton.push_back(button);

	//Enemies
	for (int i = 0; i < 50; i++) {

		auto texture = ResourceManagers::GetInstance()->GetTexture("player.png");
		enemy = std::make_shared<SpriteAnimation>(texture, 1, 24, 8, 0.2f);
		enemy->SetFlip(SDL_FLIP_HORIZONTAL);
		enemy->SetSize(40, 50);
		enemy->Set2DPosition(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIDHT);

		m_listEnemies.push_back(enemy);
	}

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

	else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
		// Lấy tọa độ của chuột
		int x, y;
		SDL_GetMouseState(&x, &y);
		// Tính góc giữa chuột và tâm của nhân vật
		double dx = x - (obj->Get2DPosition().x + obj->GetWidth() / 2);
		double dy = y - (obj->Get2DPosition().y + obj->GetHeight() / 2);
		weaponAngle = atan2(dy, dx) * 180 / M_PI;
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
			playerDirection = -1;
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
			playerDirection = 1;
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


		
		for (auto enemy : m_listEnemies) {
			GSPlay::EnemyAutoMove(enemy);

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

	//Update position of camera
	//Camera::GetInstance()->Update(deltaTime);
	//obj->Update(deltaTime);
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	m_score->Draw(renderer);
	score->Draw(renderer);
	gold->Draw(renderer);
	money->Draw(renderer);

	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}

	for (auto it : m_listAnimation)
	{

		it->Draw(renderer);

	}

	for (auto it : m_listEnemies)
	{
		it->Draw(renderer);
	}

}

void GSPlay::EnemyAutoMove(std::shared_ptr<SpriteAnimation> e)
{

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
	else
	{

	}
	
}