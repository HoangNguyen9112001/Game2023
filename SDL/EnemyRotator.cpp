#pragma once#include "EnemyRotator.h"
#include "game.h"
using namespace Tmpl8;

EnemyRotator::EnemyRotator(vec2* _pos, vec2* _dir, RotationVar* _rVar, unsigned int* _frame, MoveToADirection* _mover)
	: Rotator(_pos, _dir, _rVar, _frame, _mover)
{
}

EnemyRotator::EnemyRotator() :
	Rotator()
{
}

void EnemyRotator::Init(vec2* _pos, vec2* _dir, RotationVar* _rVar, unsigned int* _frame, MoveToADirection* _mover)
{
	Rotator::Init(_pos, _dir, _rVar, _frame, _mover);
}

void EnemyRotator::RotateToPlayer() const
{
	RotateToDirection(Game::Get().getPlayer().getPos());
}

