#include "Credit.h"
#include "GameObject/TextureManager.h"
#include "GameObject/MouseButton.h"


Credit::Credit() 
	: GameStateBase(StateType::STATE_CREDIT), cre_background(nullptr), cre_btn(std::list<std::shared_ptr<MouseButton>>{}), credit_text(nullptr)
{

}
Credit::~Credit()
{

}

void Credit::Init() {
	auto texture = ResourceManagers::GetInstance()->GetTexture("brick-bgr-credit.png");

	// background

	cre_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	cre_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	cre_background->Set2DPosition(0, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("BTN/Backward_BTN.png");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	cre_btn.push_back(button);


	//load credit game
	cre_text_color = { 255, 255, 204 };
	credit_text = std::make_shared<Text>("Data/font2.ttf", cre_text_color, 20);
	credit_text->SetSize(550, 80);
	credit_text->Set2DPosition((SCREEN_WIDTH - credit_text->GetWidth()) / 2, SCREEN_HEIGHT / 2 - 300);
	credit_text->LoadFromRenderText("Game made by our group!");
	
}
void Credit::Exit()
{

}
void Credit::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : cre_btn)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}
void Credit::Draw(SDL_Renderer* renderer)
{
	cre_background->Draw(renderer);
	//m_score->Draw();
	for (auto it : cre_btn)
	{
		it->Draw(renderer);
	}
	credit_text->Draw(renderer);
}
void Credit::Pause(){}

void Credit::Resume(){}

void Credit::HandleEvents(){}

void Credit::HandleKeyEvents(SDL_Event& e){}

void Credit::HandleMouseMoveEvents(int x, int y){}

void Credit::Update(float deltatime){}
