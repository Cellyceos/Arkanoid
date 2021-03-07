#include "FScreensCreator.h"

#include "Screens/AGameScreen.h"
#include "Screens/APauseScreen.h"
#include "Screens/AMainScreen.h"
#include "Screens/AScoreScreen.h"

TSharedPtr<AScreenState> FScreensCreator::operator ()(const TSharedPtr<class AScreensManager>& Owner, int32 StateID) const
{
	TSharedPtr<AScreenState> NewScreen = nullptr;
	switch (static_cast<EScreenType>(StateID))
	{
	case EScreenType::MainScreen:
		NewScreen = std::make_shared<AMainScreen>(Owner);
		break;
	case EScreenType::GameScreen:
		NewScreen = std::make_shared<AGameScreen>(Owner);
		break;
	case EScreenType::PauseScreen:
		NewScreen = std::make_shared<APauseScreen>(Owner);
		break;
	case EScreenType::ScoreScreen:
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
