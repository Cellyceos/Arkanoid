//
//  FScreensCreator.cpp
//  Screen Creator for Arkanoud Game.
//
//  Created by Kirill Bravichev on 03/07/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "FScreensCreator.h"

#include "Screens/AGameScreen.h"
#include "Screens/APauseScreen.h"
#include "Screens/AMainScreen.h"
#include "Screens/AScoreScreen.h"

int32 FScreensCreator::GetScreensCount() const
{
	return static_cast<int32>(GameConfig::EScreenTypes::ScoreScreen) + 1;
}

TSharedPtr<AScreenState> FScreensCreator::operator ()(const TWeakPtr<class AScreensManager>& Owner, int32 StateID) const
{
	TSharedPtr<AScreenState> NewScreen = nullptr;
	switch (static_cast<GameConfig::EScreenTypes>(StateID))
	{
	case GameConfig::EScreenTypes::MainScreen:
		NewScreen = std::make_shared<AMainScreen>(Owner);
		break;
	case GameConfig::EScreenTypes::GameScreen:
		NewScreen = std::make_shared<AGameScreen>(Owner);
		break;
	case GameConfig::EScreenTypes::PauseScreen:
		NewScreen = std::make_shared<APauseScreen>(Owner);
		break;
	case GameConfig::EScreenTypes::ScoreScreen:
		NewScreen = std::make_shared<AScoreScreen>(Owner);
		break;
	default:
		break;
	}

	if (NewScreen)
	{
		NewScreen->Init();
	}

	return NewScreen;
}
