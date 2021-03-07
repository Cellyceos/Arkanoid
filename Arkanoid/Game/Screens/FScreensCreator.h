#pragma once

#include "Interfaces/IScreensCreator.h"


enum class EScreenType
{
	MainScreen,
	GameScreen,
	PauseScreen,
	ScoreScreen,
	Unknown
};


struct FScreensCreator : IScreensCreator
{
	virtual TSharedPtr<AScreenState> operator()(const TSharedPtr<class AScreensManager>& Owner, int32 StateID) const override;
};

