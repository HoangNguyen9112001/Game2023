#include "GSOption.h"
#include "GameObject/TextureManager.h"
#include "GameObject/MouseButton.h"
#include "GSMenu.h"
#include "GSPlay.h"

GSOption::GSOption()
	: GameStateBase(StateType::STATE_OPTION)
{

}
GSOption::~GSOption()
{}

void GSOption::Init()
{

	//background
	opt_bg = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("brick-bgr.png"), SDL_FLIP_NONE);
	opt_bg->Set2DPosition(0, 0);
	opt_bg->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	//Button close
	button = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("Button/032.png"), SDL_FLIP_NONE);
	button->SetSize(70, 70);
	button->Set2DPosition(50,SCREEN_HEIGHT - 100);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});


	//high sore photo
	m_high_score = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("high_score.jpg"), SDL_FLIP_NONE);
	m_high_score->Set2DPosition(0, 0);
	m_high_score->SetSize(SCREEN_WIDTH, 300);
	// Reading file HighScore.txt
	// 
	FILE* file = fopen("Data/HighScore.txt", "r");
	if (file == nullptr)
	{
		return;
	}
	fscanf(file, "%d",&HighScore);
	
	//Best score
	SDL_Color m_textColor = { 255, 255, 204 };
	std::shared_ptr<GSPlay> score = std::make_shared<GSPlay>();
	best_score = std::make_shared<Text>("Data/calibri.ttf", m_textColor, 20);
	best_score->SetSize(70, 140);
	best_score->Set2DPosition(SCREEN_WIDTH / 2 - best_score->GetWidth() / 2,350);
	best_score->LoadFromRenderText(std::to_string(HighScore));
	fclose(file);

}
void	GSOption::Exit()
{
	
}
void	GSOption::Pause() 
{
	
}
void	GSOption::Resume()
{
}
void	GSOption::HandleEvents() 
{
}
void	GSOption::HandleKeyEvents(SDL_Event& e)
{
}
void	GSOption::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	button->HandleTouchEvent(&e);

}
void	GSOption::HandleMouseMoveEvents(int x, int y)
{
}
void	GSOption::Update(float deltaTime) 
{
	//best_score->Update(deltaTime);

}
void	GSOption::Draw(SDL_Renderer* renderer) 
{

	opt_bg->Draw(renderer);
	m_high_score->Draw(renderer);
	best_score->Draw(renderer);
	button->Draw(renderer);
}