#pragma once
#include"BaseObject.h"

class Sprite2D : public BaseObject
{
protected:
	int m_iWidth;
	int m_iHeight;
	SDL_RendererFlip m_flip;
	bool m_isBulletActive = false;
public:
	Sprite2D() : BaseObject(), m_iWidth(0), m_iHeight(0) {}
	Sprite2D( std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip);
	void Init() override;
	void Draw(SDL_Renderer * renderer) override;
	void Update(float deltatime) override;

	void DrawOriginal(SDL_Renderer* renderer);
	void		Set2DPosition(float x, float y);
	Vector3		Get2DPosition();
	void		SetSize(int width, int height);
	int			GetWidth();
	int			GetHeight();
	void		SetRotation(double angle);
	double		GetRotation();
	void		SetFlip(SDL_RendererFlip flip);
	void SetBulletActive(bool isActive);
	bool GetBulletActive();
	
};

