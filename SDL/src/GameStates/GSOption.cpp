#include "GSOption.h"
#include "GameObject/TextureManager.h"
#include "GameObject/MouseButton.h"
#include "GSMenu.h"

GSOption::GSOption()
	: GameStateBase(StateType::STATE_OPTION), opt_bg(nullptr), opt_bt(std::list<std::shared_ptr<MouseButton>>{})
{

}
GSOption::~GSOption()
{}
void GSOption::Init()
{

	//background
	opt_bg = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("bg_menu.tga"), SDL_FLIP_NONE);
	opt_bg->Set2DPosition(0, 0);
	opt_bg->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);

	//Button close
	button = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("btn_close.tga"), SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	opt_bt.push_back(button);

	//menu option 
	menu_opt = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("menu_opt.png"), SDL_FLIP_NONE);
	menu_opt->SetSize(700, 500);
	menu_opt->Set2DPosition((SCREEN_WIDTH - menu_opt->GetWidth()) / 2, (SCREEN_HEIDHT - menu_opt->GetHeight()) / 2);

	//Music 
	music_on_bt = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("btn_music.tga"), SDL_FLIP_NONE);
	music_on_bt->SetSize(70,70);
	music_on_bt->Set2DPosition((SCREEN_WIDTH - menu_opt->GetWidth()) / 2 + menu_opt->GetWidth() / 3 - music_on_bt->GetWidth()/2,
								(SCREEN_HEIDHT - menu_opt->GetHeight())/2 + menu_opt->GetHeight() / 3);
	music_on_bt->SetOnClick([this]() {
		Mix_Resume(-1);
		});
	opt_bt.push_back(music_on_bt);

	music_off_bt = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("btn_music_off.tga"), SDL_FLIP_NONE);
	music_off_bt->SetSize(70, 70);
	music_off_bt->Set2DPosition((SCREEN_WIDTH - menu_opt->GetWidth()) / 2 + menu_opt->GetWidth()* 2 / 3 - music_off_bt->GetWidth() / 2,
								(SCREEN_HEIDHT - menu_opt->GetHeight()) / 2 + menu_opt->GetHeight() / 3);
	music_off_bt->SetOnClick([this]() {
		&Sound::StopSound;
		});
	opt_bt.push_back(music_off_bt);

	//SFX 
	sfx_on_bt = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("btn_sfx.tga"), SDL_FLIP_NONE);
	sfx_on_bt->SetSize(70, 70);
	sfx_on_bt->Set2DPosition((SCREEN_WIDTH - menu_opt->GetWidth()) / 2 + menu_opt->GetWidth() / 3 - sfx_on_bt->GetWidth() / 2,
		(SCREEN_HEIDHT - menu_opt->GetHeight()) / 2 + menu_opt->GetHeight() * 2 / 3 - sfx_on_bt->GetHeight() * 2 / 3);
	sfx_on_bt->SetOnClick([this]() {
		
		});
	opt_bt.push_back(sfx_on_bt);

	sfx_off_bt = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("btn_sfx_off.tga"), SDL_FLIP_NONE);
	sfx_off_bt->SetSize(70, 70);
	sfx_off_bt->Set2DPosition((SCREEN_WIDTH - menu_opt->GetWidth()) / 2 + menu_opt->GetWidth() * 2 / 3 - sfx_off_bt->GetWidth() / 2,
		(SCREEN_HEIDHT - menu_opt->GetHeight()) / 2 + menu_opt->GetHeight() * 2 / 3 - sfx_off_bt->GetHeight() * 2/3);
	sfx_off_bt->SetOnClick([this]() {

		});
	opt_bt.push_back(sfx_off_bt);
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
	for (auto button : opt_bt)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}
void	GSOption::HandleMouseMoveEvents(int x, int y)
{
}
void	GSOption::Update(float deltaTime) 
{
}
void	GSOption::Draw(SDL_Renderer* renderer) 
{

	opt_bg->Draw(renderer);
	for (auto it : opt_bt)
	{
		it->Draw(renderer);
	}
	menu_opt->Draw(renderer);
}