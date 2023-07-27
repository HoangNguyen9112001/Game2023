#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "GSMenu.h"
#include "SDL.h";
#include "SDL_mixer.h"


// tính khoảng cách giữa hai điểm
float distance(float x1, float y1, float x2, float y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// check VAR
bool intersect(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
	return !(x1 > x2 + w2 || x1 + w1 < x2 || y1 > y2 + h2 || y1 + h1 < y2);
}

//variables for decreasing health and flashing sprite during invulnerability period
bool isInvulnerable = false;
bool isSpriteVisible = true;
bool hasCollided = false;
Uint32 resetInvulnerability(Uint32 interval, void* param);
Uint32 toggleSpriteVisibility(Uint32 interval, void* param);

//Varialbe to check if the game is over	
bool isGameOver = false;


//player is picked
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

	auto texture = ResourceManagers::GetInstance()->GetTexture("Asset/background4.png");
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
	texture = ResourceManagers::GetInstance()->GetTexture("BTN/Close_BTN.png");
	button = std::make_shared<MouseButton>( texture, SDL_FLIP_NONE);
	button->SetSize(60, 60);
	button->Set2DPosition(SCREEN_WIDTH - 75, 20);
	button->SetOnClick([this]() {
		//GameStateMachine::GetInstance()->PopState();
		//GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		Exit();
		});
	m_listButton.push_back(button);


	// Pause button
	button = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("BTN/Pause_BTN.png"), SDL_FLIP_NONE);
	button->SetSize(60, 60);
	button->Set2DPosition(SCREEN_WIDTH - 150, 20);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PAUSE);
		Pause();
		});
	m_listButton.push_back(button);

	//Victory
	auto textureVictory = ResourceManagers::GetInstance()->GetTexture("victory3.png");
	m_victoryIcon = std::make_shared<Sprite2D>(textureVictory, SDL_FLIP_NONE);
	m_victoryIcon->Set2DPosition(SCREEN_WIDTH/2 - 350, SCREEN_HEIGHT/2 -300 );
	m_victoryIcon->SetSize(700, 600);

	auto textureVictoryButton = ResourceManagers::GetInstance()->GetTexture("BTN/Forward_BTN.png");
	m_nextButton = std::make_shared<MouseButton>(textureVictoryButton, SDL_FLIP_NONE);
	m_nextButton->Set2DPosition(SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 2 + 50);
	m_nextButton->SetSize(50, 50);
	m_nextButton->SetOnClick([this]() {
		isGameOver = false;
		Exit();
		//GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	//End game
	auto textureEndGame = ResourceManagers::GetInstance()->GetTexture("gameover.png");
	m_endGameButton = std::make_shared<MouseButton>(textureEndGame, SDL_FLIP_NONE);
	m_endGameButton->Set2DPosition(SCREEN_WIDTH / 2 - 450, SCREEN_HEIGHT / 2 - 225);
	m_endGameButton->SetSize(900, 450);
	m_endGameButton->SetOnClick([this]() {
		isGameOver = false;
		//GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		Exit();
		});

   // Pick Player
	//Player1
	if (i == 0) {
		texture = ResourceManagers::GetInstance()->GetTexture("Asset/Player.tga");
		player = std::make_shared<SpriteAnimation>(texture, 1, 3, 1, 0.2f);
		player->SetFlip(SDL_FLIP_HORIZONTAL);
		player->SetSize(40, 50);
		player->Set2DPosition(350, 400);
		m_listAnimation.push_back(player);
	}

	//player2
	if (i == 1) {
		texture = ResourceManagers::GetInstance()->GetTexture("Asset/Player2.tga");
		player = std::make_shared<SpriteAnimation>(texture, 1, 6, 1, 0.1f);
		player->SetFlip(SDL_FLIP_HORIZONTAL);
		player->SetSize(40, 50);
		player->Set2DPosition(350, 400);
		m_listAnimation.push_back(player);
	}
	
	//SCORE
	m_textColor = { 255, 255, 204 };
	m_score = std::make_shared<Text>("Data/MochiyPopOne.ttf", m_textColor, 20);
	m_score->SetSize(75, 30);
	m_score->Set2DPosition((SCREEN_WIDTH - m_score->GetWidth()) / 3, 45);
	m_score->LoadFromRenderText("Score: ");
	
	score = std::make_shared<Text>("Data/MochiyPopOne.ttf", m_textColor, 14);
	score->SetSize(50,50);
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

	////gold
	//m_gold = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("gold_icon.png"), SDL_FLIP_NONE);
	//m_gold->SetSize(60, 60);
	//m_gold->Set2DPosition(score->Get2DPosition().x + score->GetWidth() + 50, 20);

	//gold = std::make_shared<Text>("Data/font2.ttf", m_textColor, 14);
	////TTF_SizeText(m_font, std::to_string(golds).c_str(), &m_textwidth, &m_textheight);
	//gold->SetSize(m_textwidth, m_textheight);
	//gold->Set2DPosition(m_gold->Get2DPosition().x + m_gold->GetWidth() + 10, 30);
	//gold->LoadFromRenderText(std::to_string(golds));

	////Guns shop
	//button = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("guns_shop_icon.png"), SDL_FLIP_HORIZONTAL);
	//button->SetSize(60, 60);
	//button->Set2DPosition(SCREEN_WIDTH - 230, 20);
	//button->SetOnClick([this]() {

	//	});
	//m_listButton.push_back(button);

	//Enemies
	for (int i = 0; i < MAX_ENEMIES; ++i) {

		texture = ResourceManagers::GetInstance()->GetTexture("Asset/ZombieSprite.tga");
		enemy = std::make_shared<SpriteAnimation>(texture, 1, 3, 1, 0.9f);
		enemy->SetFlip(SDL_FLIP_NONE);
		enemy->SetSize(40, 50);
		enemy->Set2DPosition(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
		enemy->SetEnemyAlive(true);
		m_listEnemies.push_back(enemy);
	}

	//Camera::GetInstance()->SetTarget(obj);
	


	// Sound
	BgSound = std::make_shared<Sound>("Data/Sounds/BgSoundPlay.mp3");
	BgSound->PlaySound();
	BgSound->LoadSound("Data/Sounds/BgSoundPlay.mp3");
	
	

	/*auto Shooting = std::make_shared<Sound>("Data/Sounds/Shooting.mp3");
	Shooting->LoadSound("Data/Sounds/Shooting.mp3");
	Shooting->PlaySound();*/


	////Sound
	/*m_Sound1 = std::make_shared<Sound>("Data/Sounds/Alarm01.wav");
	m_Sound1->PlaySound();
	m_Sound1->LoadSound("Data/Sounds/Alarm01.wav");*/


	
	//Mix_Chunk* explosionSound = Mix_LoadWAV("Data/Sounds/Alarm01.wav");

	//Mix_PlayChannel(-1, gunshotSound, 0);
	//Mix_PlayChannel(-1, explosionSound, 0);

	m_KeyPress = 0;
}

void GSPlay::Exit()
{
	BgSound->StopSound();
	GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
}

void GSPlay::Pause()
{
	BgSound->PauseSound();
	//BgSound->StopSound();
}

void GSPlay::Resume()
{
	BgSound->ResumeSound();
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
			Mix_Chunk* gunshotSound = Mix_LoadWAV("Data/Sounds/Shooting.mp3");
			Mix_PlayChannel(-1, gunshotSound, 0);
			/*auto Shooting = std::make_shared<Sound>("Data/Sounds/Shooting.mp3");
			Shooting->LoadSound("Data/Sounds/Shooting.mp3");
			Shooting->PlaySound();*/
			for (auto& it : m_listBullets)
			{
				
				int curentTime = SDL_GetTicks();
				//create bullet
				if (!it->GetBulletActive())//if no bullet active
				{
					//Pause();
					
					if (curentTime - m_lastShootTime > m_shootDelay) {

						it->Set2DPosition(weapon->Get2DPosition().x  + weapon->GetWidth() / 2,
							weapon->Get2DPosition().y + weapon->GetHeight() / 2);
						it->SetRotation(weaponAngle);
						it->SetBulletActive(true);
						m_lastShootTime = curentTime;
						//Shooting->StopSound();
					}
				}
			}
		}
		
	}
}

void GSPlay::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto& button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
	if (playerHealth < 1) {
		m_endGameButton->HandleTouchEvent(&e);
	}
	if (isGameOver) {
		m_nextButton->HandleTouchEvent(&e);
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{

}

float time1 = 0.0f;
void GSPlay::Update(float deltaTime)
{
	if (!isGameOver) {
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
			weapon = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("Asset/gun.png"),
				playerDirection == 1 ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL);
			weapon->SetRotation(weaponAngle);
			weapon->SetSize(50, 20);

			//get hand posision

			double handX = player->Get2DPosition().x + player->GetWidth() / 2 + cos(weaponAngle * M_PI / 180) * 25;
			double handY = player->Get2DPosition().y + player->GetHeight() / 2 + sin(weaponAngle * M_PI / 180) * 25;

			//set gun on hand
			weapon->Set2DPosition(handX - weapon->GetWidth() / 2, handY - weapon->GetHeight() / 2);

			//Move pplayer
			switch (m_KeyPress) {
			case 1: // Move left
				if (player->Get2DPosition().x < 50)
				{
					player->Set2DPosition(50, player->Get2DPosition().y);
				}
				else {
					player->SetFlip(SDL_FLIP_HORIZONTAL);
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
				if (player->Get2DPosition().x > SCREEN_WIDTH - player->GetWidth() - 50)
				{
					player->Set2DPosition(SCREEN_WIDTH - player->GetWidth() -50, player->Get2DPosition().y);
				}
				else {
					player->SetFlip(SDL_FLIP_NONE);
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
			// Collision with Bullet
			if (it->GetEnemyLive()) { // if enemy is alive
				for (auto& bul : m_listBullets)
				{
					if (bul->GetBulletActive()) // if bullet is flying
					{
						if (intersect(bul->Get2DPosition().x, bul->Get2DPosition().y, bul->GetWidth(), bul->GetHeight(),
							it->Get2DPosition().x, it->Get2DPosition().y, it->GetWidth(), it->GetHeight()))
						{	//check VAR

							bul->SetBulletActive(false);
							it->SetEnemyAlive(false);
							//update scores
							scores += 5;
							score->LoadFromRenderText(std::to_string(scores));
						
						}
					}
				}

				//enemy VAR player
				if (intersect(player->Get2DPosition().x + 5, player->Get2DPosition().y , player->GetWidth() -10, player->GetHeight(),
					it->Get2DPosition().x + 11, it->Get2DPosition().y + 10, it->GetWidth() - 22, it->GetHeight() - 20)) {

					if (!isInvulnerable) { //nếu player không trong trạng thái không thể bị chỉ định 
						// Reduce character's health here
						playerHealth--;
						// Set the character to be invulnerable
						isInvulnerable = true;
						// Set a timer for the invulnerability cooldown period 
						int invulnerabilityCooldown = 3000;
						SDL_AddTimer(invulnerabilityCooldown, resetInvulnerability, NULL);

						// Set up a timer for toggling sprite visibility 
						int flashingInterval = 200; // Adjust this value to control the flashing speed
						SDL_AddTimer(flashingInterval, toggleSpriteVisibility, NULL);

						hasCollided = true;
					}

				}
				if ((player->Get2DPosition().x) <= (it->Get2DPosition().x)) {
					it->SetFlip(SDL_FLIP_HORIZONTAL);
				}
				else if ((player->Get2DPosition().x) > (it->Get2DPosition().x)) {
					it->SetFlip(SDL_FLIP_NONE);
				}
			}
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

		// Spaw Enemies

		time1 += deltaTime;

		//spawn enemy
		if (time1 >= 1.5f)
		{
			for (int i = 0; i < MAX_ENEMIES; ++i) {

				auto texture = ResourceManagers::GetInstance()->GetTexture("Asset/ZombieSprite.tga");
				enemy = std::make_shared<SpriteAnimation>(texture, 1, 3, 1, 0.9f);
				enemy->SetFlip(SDL_FLIP_NONE);
				enemy->SetSize(40, 50);
				enemy->Set2DPosition(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
				enemy->SetEnemyAlive(true);
				m_listEnemies.push_back(enemy);
			}

			time1 = 0.0f;
		}

		currentTime = SDL_GetTicks();
		elapsedTime = currentTime - startTime;

		if (elapsedTime >= 1000)
		{
			if (countdown <= 1)
			{
				countdown = 1;
			}
			countdown--;
			startTime = currentTime;
		}

		int minutes = countdown / 60;
		int seconds = countdown % 60;


		
		min = std::make_shared<Text>("Data/MochiyPopOne.ttf", m_textColor, 14);
		//TTF_SizeText(m_font, std::to_string(golds).c_str(), &m_textwidth, &m_textheight);
		min->SetSize(50, 50);
		min->Set2DPosition(500, 30);
		min->LoadFromRenderText(std::to_string(minutes) + ": ");

		sec = std::make_shared<Text>("Data/MochiyPopOne.ttf", m_textColor, 14);
		//TTF_SizeText(100, std::to_string(golds).c_str(), &m_textwidth, &m_textheight);
		sec->SetSize(50, 50);
		sec->Set2DPosition(550, 30);
		if (seconds < 10) {
			sec->LoadFromRenderText("0 " + std::to_string(seconds));
		}
		else
		{
			sec->LoadFromRenderText(std::to_string(seconds));
		}
		

		if (minutes<1 && seconds <1) {
			if (scores > bestScore)
				bestScore = scores;
			GSPlay::WriteHighScore();
			isGameOver = true;
		}
	}

	if (playerHealth < 1) {
		if (scores > bestScore)
			bestScore = scores;
		GSPlay::WriteHighScore();
		isGameOver = true;
	}

}

void GSPlay::drawRect(SDL_Renderer* renderer)
{
	SDL_Rect hitboxRect;
	hitboxRect.x = static_cast<int>(player->Get2DPosition().x + 18);
	hitboxRect.y = static_cast<int>(player->Get2DPosition().y + 17);
	hitboxRect.w = player->GetWidth() - 36;
	hitboxRect.h = player->GetHeight() - 37;
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &hitboxRect);
}

void GSPlay::drawEnemyRect(SDL_Renderer* renderer)
{
	SDL_Rect enemyRect;
	enemyRect.x = static_cast<int>(enemy->Get2DPosition().x + 11);
	enemyRect.y = static_cast<int>(enemy->Get2DPosition().y + 10);
	enemyRect.w = enemy->GetWidth() - 22;
	enemyRect.h = enemy->GetHeight() - 20;
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderDrawRect(renderer, &enemyRect);
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	m_score->Draw(renderer);
	score->Draw(renderer);
	/*gold->Draw(renderer);*/
	/*m_gold->Draw(renderer);*/
	weapon->Draw(renderer);
	min->Draw(renderer);
	sec->Draw(renderer);

	//Draw heart
	if (playerHealth > 0)
	{
		m_heartIcons[0]->Draw(renderer);
	}
	if (playerHealth > 1)
	{
		m_heartIcons[1]->Draw(renderer);
	}
	if (playerHealth > 2)
	{
		m_heartIcons[2]->Draw(renderer);
	}

	//Render Button
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}

	//Render player
	for (auto it : m_listAnimation)
	{

			if (isSpriteVisible) {
				it->Draw(renderer);
			}
		
		
		

	}
	//drawRect(renderer);

	//Render Enemy
	for (auto it : m_listEnemies)
	{
		if(it->GetEnemyLive())
			it->Draw(renderer);
	}
	//drawEnemyRect(renderer);
	//Render Bullet
	for (auto it : m_listBullets)
	{
		if (it->GetBulletActive())
			it->Draw(renderer);
	}

	//Show game over
	if (playerHealth < 1) {

		m_endGameButton->Draw(renderer);
	}
	if (isGameOver && playerHealth >= 1) {
		m_victoryIcon->Draw(renderer);
		m_nextButton->Draw(renderer);
	}
}

//Reset invulnerable state
Uint32 resetInvulnerability(Uint32 interval, void* param) {
	isInvulnerable = false;
	hasCollided = false;
	if (!isInvulnerable) {
		// Reset the sprite visibility to be visible
		isSpriteVisible = true;
		return 0;
	}
	return interval;
}

//Toggle sprite visibility to make flashing effect
Uint32 toggleSpriteVisibility(Uint32 interval, void* param) {
	if (isInvulnerable && hasCollided) {
		isSpriteVisible = !isSpriteVisible;
	}
	if (isInvulnerable) {
		return interval;
	}
	isSpriteVisible = true;
	return 0;
	/*isSpriteVisible = !isSpriteVisible;
	if (isInvulnerable) {
		return interval;
	}
	isSpriteVisible = true;
	return 0;*/
}

void GSPlay::EnemyAutoMove(std::shared_ptr<SpriteAnimation> e)
{

	m_enemySpeed = 1;
	//tinh go'c giua enemy vs palyer
	float angle = atan2(player->Get2DPosition().y - e->Get2DPosition().y, player->Get2DPosition().x - e->Get2DPosition().x);
	//tinh khoang cach
	float dist = distance(player->Get2DPosition().x, player->Get2DPosition().y, e->Get2DPosition().x, e->Get2DPosition().y);

	if (dist > 10)
	{
		float a = e->Get2DPosition().x;
		a += cos(angle) * m_enemySpeed;
		float b = e->Get2DPosition().y;
		b += sin(angle) * m_enemySpeed;

		e->Set2DPosition(a, b);
		dist = distance(player->Get2DPosition().x, player->Get2DPosition().y, a, b);
	}
	
}

void GSPlay::WriteHighScore()
{
	FILE* file = fopen("Data/HighScore.txt","w");
	if (file == nullptr)
	{
		return;
	}
	fprintf(file, "%d",bestScore);
	fclose(file);
}

int GSPlay::GetHighScore()
{
	if(scores > bestScore) return scores;
	return bestScore;
}

void GSPlay::UpdateValue(int& value, int upd)
{
	value = upd;
}





