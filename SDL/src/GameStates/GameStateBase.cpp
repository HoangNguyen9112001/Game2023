#include "GameStateBase.h"
#include "GameStates/GSIntro.h"
#include "GSMenu.h"
#include "GSPlay.h"
#include "Credit.h"
#include "GSOption.h"
#include "GSPause.h"
#include "GSEndGame.h"


GameStateBase::GameStateBase(StateType stateType) : m_stateType(stateType)
{}

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateType stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case StateType::STATE_INVALID:
		break;
	case StateType::STATE_INTRO:
		gs = std::make_shared<GSIntro>();
		//GSINTRO;
		break;
	case StateType::STATE_MENU:
		gs = std::make_shared<GSMenu>();
		//GSMENU
		break;
	case StateType::STATE_PLAY:
		gs = std::make_shared<GSPlay>();
		//GSPLAY
		break;
	case StateType::STATE_CREDIT:
		//GSCREDIT
		gs = std::make_shared<Credit>();
		break;
	case StateType::STATE_OPTION:
		//GSOPTION
		gs = std::make_shared<GSOption>();
	case StateType::STATE_PAUSE:
		//GSOPTION
		gs = std::make_shared<GSPause>();
		break;
	case StateType::STATE_ENDGAME:
		//GSENDGAME
		gs = std::make_shared<GSEndGame>();
		break;
	default:
		break;
	}
	return gs;
}

StateType GameStateBase::GetGameStateType()
{
	return m_stateType;
}
