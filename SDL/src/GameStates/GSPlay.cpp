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

extern int i;

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
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	// heart icon
	texture = ResourceManagers::GetInstance()->GetTexture("heart.tga");
	m_heartIcon = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_heartIcon->Set2DPosition(50, 50);
	m_heartIcon->SetSize(50, 50);
	m_heartIcons.push_back(m_heartIcon);


	m_heartIcon = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_heartIcon->Set2DPosition(100, 50);
	m_heartIcon->SetSize(50, 50);
	m_heartIcons.push_back(m_heartIcon);

	m_heartIcon = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_heartIcon->Set2DPosition(150, 50);
	m_heartIcon->SetSize(50, 50);
	m_heartIcons.push_back(m_heartIcon);

	// Close button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>( texture, SDL_FLIP_NONE);
	button->SetSize(60, 60);
	button->Set2DPosition(SCREEN_WIDTH - 75, 20);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	m_listButton.push_back(button);


	// Pause button
	button = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("btn_pause.tga"), SDL_FLIP_NONE);
	button->SetSize(60, 60);
	button->Set2DPosition(SCREEN_WIDTH - 150, 20);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PAUSE);
		});
	m_listButton.push_back(button);

   //pick Player
	//player1
	if (i == 0) {
		texture = ResourceManagers::GetInstance()->GetTexture("player.png");
		player = std::make_shared<SpriteAnimation>(texture, 1, 24, 8, 0.2f);
		player->SetFlip(SDL_FLIP_HORIZONTAL);
		player->SetSize(60, 80);
		player->Set2DPosition(350, 400);
		m_listAnimation.push_back(player);
	}

	//player2
	if (i == 1 ) {
		texture = ResourceManagers::GetInstance()->GetTexture("player2.tga");
		player = std::make_shared<SpriteAnimation>(texture, 1, 2, 8, 0.9f);
		player->SetFlip(SDL_FLIP_HORIZONTAL);
		player->SetSize(60, 80);
		player->Set2DPosition(350, 400);
		m_listAnimation.push_back(player);
	}
	
	//SCORE
	m_textColor = { 0, 0, 255 };
	m_score = std::make_shared<Text>("Data/font2.ttf", m_textColor, 20);
	m_score->SetSize(75, 30);
	m_score->Set2DPosition((SCREEN_WIDTH - m_score->GetWidth()) / 3, 45);
	m_score->LoadFromRenderText("Score: ");
	
	score = std::make_shared<Text>("Data/font2.ttf", m_textColor, 14);
	//TTF_SizeText(m_font, std::to_string(scores).c_str(), &m_textwidth, &m_textheight);
	score->SetSize(m_textwidth, m_textheight);
	score->Set2DPosition(m_score->Get2DPosition().x + m_score->GetWidth() + 5, 30);
	score->LoadFromRenderText(std::to_string(scores));

	//Bullet
	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		bullet = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("bullet.png"), SDL_FLIP_NONE);
		bullet->SetSize(20, 20);
		bullet->SetBulletActive(false);// = false;
		m_listBullets.push_back(bullet);
	}

	//gold
	m_gold = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("gold_icon.png"), SDL_FLIP_NONE);
	m_gold->SetSize(60, 60);
	m_gold->Set2DPosition(score->Get2DPosition().x + score->GetWidth() + 50, 20);

	gold = std::make_shared<Text>("Data/font2.ttf", m_textColor, 14);
	//TTF_SizeText(m_font, std::to_string(golds).c_str(), &m_textwidth, &m_textheight);
	gold->SetSize(m_textwidth, m_textheight);
	gold->Set2DPosition(m_gold->Get2DPosition().x + m_gold->GetWidth() + 10, 30);
	gold->LoadFromRenderText(std::to_string(golds));

	//Guns shop
	button = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("guns_shop_icon.png"), SDL_FLIP_HORIZONTAL);
	button->SetSize(60, 60);
	button->Set2DPosition(SCREEN_WIDTH - 230, 20);
	button->SetOnClick([this]() {

		});
	m_listButton.push_back(button);

	//Enemies
	for (int i = 0; i < MAX_ENEMIES; ++i) {

		texture = ResourceManagers::GetInstance()->GetTexture("player2.tga");
		enemy = std::make_shared<SpriteAnimation>(texture, 1, 2, 8, 0.9f);
		enemy->SetFlip(SDL_FLIP_NONE);
		enemy->SetSize(40, 50);
		enemy->Set2DPosition(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
		enemy->SetEnemyAlive(true);
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
	switch (e.type) {
		//If a key was pressed
	case SDL_KEYDOWN:
		if (e.key.repeat == 0)//For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				m_KeyPress |= 1 << 3;
				break;
			case SDLK_s:
				m_KeyPress |= 1 << 1;
				break;
			case SDLK_a:
				m_KeyPress |= 1;
				break;
			case SDLK_d:
				m_KeyPress |= 1 << 2;
				break;
			default:
				break;
			}

		}
		break;
		//Key Up
	case SDL_KEYUP:
		if (e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_a:
				m_KeyPress ^= 1;
				break;
			case SDLK_s:
				m_KeyPress ^= 1 << 1;
				break;
			case SDLK_d:
				m_KeyPress ^= 1 << 2;
				break;
			case SDLK_w:
				m_KeyPress ^= 1 << 3;
				break;
			default:
				break;
			}

		}
		break;
		//Mouse Motion
	case SDL_MOUSEMOTION:
		weaponAngle = atan2(e.motion.y - weapon->Get2DPosition().y, e.motion.x - weapon->Get2DPosition().x) * 180 / M_PI;
		break;
		//Bullet fly
	case SDL_MOUSEBUTTONDOWN:
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			for (auto& it : m_listBullets)
			{
				int curentTime = SDL_GetTicks();
				//create bullet
				if (!it->GetBulletActive())//if no bullet active
				{
					if (curentTime - m_lastShootTime > m_shootDelay) {
						it->Set2DPosition(weapon->Get2DPosition().x  + weapon->GetWidth() / 2,
							weapon->Get2DPosition().y + weapon->GetHeight() / 2);
						it->SetRotation(weaponAngle);
						it->SetBulletActive(true);
						m_lastShootTime = curentTime;
					}
				}
			}
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

//float time1 = 0.0f;
void GSPlay::Update(float deltaTime)
{
	switch (m_KeyPress)//Handle Key event
	{
	default:
		break;
	}
	//Update Button
	for (auto& it : m_listButton)
	{
		it->Update(deltaTime);
	}
	//Update Player
	for (auto& it : m_listAnimation)
	{
		// Gun rotation
		weapon = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("weaponR1.png"),
											playerDirection == 1 ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL);
		weapon->SetRotation(weaponAngle);
		weapon->SetSize(50, 20);

		//get hand posision

		double handX = player->Get2DPosition().x + player->GetWidth() / 2 + cos(weaponAngle * M_PI / 180) * 25 ;
		double handY = player->Get2DPosition().y + player->GetHeight() / 2 + sin(weaponAngle * M_PI / 180) * 25;

		//set gun on hand
		weapon->Set2DPosition(handX - weapon->GetWidth() / 2, handY - weapon->GetHeight() / 2);

		//Move Player
		switch (m_KeyPress) {
		case 1: // Move left
				if (player->Get2DPosition().x < 0)
				{
					player->Set2DPosition(0, player->Get2DPosition().y);
				}
				else {
					playerDirection = -1;
					it->MoveLeft(deltaTime);
				}
			break;
		case 2: // Move down
			if (player->Get2DPosition().y > SCREEN_HEIGHT - player->GetHeight()) {
				player->Set2DPosition(player->Get2DPosition().x, SCREEN_HEIGHT - player->GetHeight());
			}
			else
				it->MoveDown(deltaTime);
			break;
		case 4: // Move right
			if (player->Get2DPosition().x > SCREEN_WIDTH - player->GetWidth())
			{
				player->Set2DPosition(SCREEN_WIDTH - player->GetWidth(), player->Get2DPosition().y);
			}
			else {
				playerDirection = 1;
				it->MoveRight(deltaTime);
			}
			break;
		case 8: // Move up
			if (player->Get2DPosition().y < 0) {
				player->Set2DPosition(player->Get2DPosition().x, 0);
			}
			else
				it->MoveUp(deltaTime);
			break;
		default:
			break;
		}
		it->Update(deltaTime);

	}
	//time1 += deltaTime;
	//Update Enemy
	for (auto& it : m_listEnemies) {
		GSPlay::EnemyAutoMove(it);

		float ex = it->Get2DPosition().x;
		float ey = it->Get2DPosition().y;
		float ew = it->GetWidth();
		float eh = it->GetHeight();

		// Collision with Bullet
		if (it->GetEnemyLive()) { // if enemy is alive
			for (auto& bul : m_listBullets)
			{
				if (bul->GetBulletActive()) // if bullet is flying
				{
					float bx = bul->Get2DPosition().x;
					float by = bul->Get2DPosition().y;
					float bw = bul->GetWidth();
					float bh = bul->GetHeight();

					if (intersect(bx, by, bw, bh, ex, ey, ew, eh))
					{	//check VAR
						bul->SetBulletActive(false);
						it->SetEnemyAlive(false);
						gold_cnt += 10;
						score_cnt += 5;
						break;
					}
				}
			}
		}
		gold->Update(deltaTime);
		score->Update(deltaTime);
		it->Update(deltaTime);
	}
	//Update Bullet
	for (auto& it : m_listBullets)
	{
		//shoot
		if (it->GetBulletActive())
		{
			float x = it->Get2DPosition().x;
			float y = it->Get2DPosition().y;
			float r = it->GetRotation();
			// shooting
			x += m_bullet_speed * cos(r * M_PI / 180);
			y += m_bullet_speed * sin(r * M_PI / 180);

			it->Set2DPosition(x, y);
			// Collision with screen
			if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT)
			{
				it->SetBulletActive(false);
			}
		}
		it->Update(deltaTime);
	}

	GSPlay::UpdateValue(golds, gold_cnt);
	GSPlay::UpdateValue(scores, score_cnt);
	gold->Update(deltaTime);
	score->Update(deltaTime);
}


void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	m_score->Draw(renderer);
	score->Draw(renderer);
	gold->Draw(renderer);
	m_gold->Draw(renderer);
	weapon->Draw(renderer);

	//Draw heart
	//if (playerHealth > 0)
	//{
	//	m_heartIcons[0]->Draw(renderer);
	//}
	//if (playerHealth > 1)
	//{
	//	m_heartIcons[1]->Draw(renderer);
	//}
	//if (playerHealth > 2)
	//{
	//	m_heartIcons[2]->Draw(renderer);
	//}

	
	//Render Button
	for (auto& it : m_listButton)
	{
		it->Draw(renderer);
	}

	//Render player
	for (auto& it : m_listAnimation)
	{

		it->Draw(renderer);

	}

	//Render Enemy
	for (auto& it : m_listEnemies)
	{
		if(it->GetEnemyLive())
			it->Draw(renderer);
	}

	//Render Bullet
	for (auto& it : m_listBullets)
	{
		if (it->GetBulletActive())
			it->Draw(renderer);
	}

}

void GSPlay::EnemyAutoMove(std::shared_ptr<SpriteAnimation> e)
{

	m_enemySpeed = 1;
	//tinh go'c giua enemy vs palyer
	float angle = atan2(player->Get2DPosition().y - e->Get2DPosition().y, player->Get2DPosition().x - e->Get2DPosition().x);
	//tinh khoang cach
	float dist = distance(player->Get2DPosition().x, player->Get2DPosition().y, e->Get2DPosition().x, e->Get2DPosition().y);

	if (dist > 20)
	{
		float a = e->Get2DPosition().x;
		a += cos(angle) * m_enemySpeed;
		float b = e->Get2DPosition().y;
		b += sin(angle) * m_enemySpeed;

		e->Set2DPosition(a, b);
		dist = distance(player->Get2DPosition().x, player->Get2DPosition().y, a, b);
	}
	
}

void GSPlay::UpdateValue(int& value, int upd)
{
	value = upd;
}
