#include "FScreensCreator.h"

#include "Screens/AGameScreen.h"
#include "Screens/APauseScreen.h"
#include "Screens/AMainScreen.h"
#include "Screens/AScoreScreen.h"

TUniquePtr<AScreenState> FScreensCreator::operator ()(const TSharedPtr<class AScreensManager>& Owner, int32 StateID) const
{
	switch (static_cast<EScreenType>(StateID))
	{
	case EScreenType::MainScreen:
		return std::make_unique<AMainScreen>(Owner);
	case EScreenType::GameScreen:
		return std::make_unique<AGameScreen>(Owner);
	case EScreenType::PauseScreen:
		return std::make_unique<APauseScreen>(Owner);
	case EScreenType::ScoreScreen:
		return std::make_unique<AScoreScreen>(Owner);
	default:
		return nullptr;
	}	
}
