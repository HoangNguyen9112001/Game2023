#include "GameStateBase.h"

class Sprite2D;
class Text;
class MouseButton;


class GSPause :
	public GameStateBase
{
public:
	GSPause();
	~GSPause();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;
	int m_KeyPress;
private:
	std::shared_ptr<Sprite2D>				m_background;
	std::shared_ptr<Sprite2D>				m_boder;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::shared_ptr<Text>					m_textGameSetting;
	std::shared_ptr<Text>					m_textGameVolumn;

	SDL_Color color;
	std::shared_ptr<MouseButton> m_soundButtonPlay;
	std::shared_ptr<MouseButton> m_soundButtonOff;
};
