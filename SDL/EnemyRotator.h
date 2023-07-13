#pragma once
#include "Rotator.h"

class EnemyRotator : public Rotator
{
public:
	EnemyRotator(Tmpl8::vec2* _pos, Tmpl8::vec2* _dir, RotationVar* _rVar, unsigned int* _frame,
		MoveToADirection* _mover);
	EnemyRotator();
	void Init(Tmpl8::vec2* _pos, Tmpl8::vec2* _dir, RotationVar* _rVar, unsigned int* _frame, MoveToADirection* _mover);
	~EnemyRotator() = default;
	void RotateToPlayer() const;
};
