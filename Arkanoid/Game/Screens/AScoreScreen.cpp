//
//  ScoreScreen.cpp
//  Score Screen State.
//
//  Created by Kirill Bravichev on 03/06/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Screens/AScoreScreen.h"
#include "AScoreManager.h"


AScoreScreen::AScoreScreen(const TWeakPtr<class AScreensManager>& InOwner) : AScreenState(InOwner)
{

}

AScoreScreen::~AScoreScreen()
{
	LOG("~AScoreScreen\n");
}

void AScoreScreen::Init()
{
	BindKey(EInputKey::Escape, std::bind(&AScoreScreen::Continue, this, _1));
}

void AScoreScreen::Continue(EInputState KeyEvent)
{
	if (KeyEvent == EInputState::Pressed)
	{
		RequestTransition(static_cast<int32>(GameConfig::EScreenTypes::MainScreen), static_cast<int32>(GameConfig::EScreenRequestReason::Default));
	}
}

void AScoreScreen::Draw(const TSharedPtr<ARendererClass>& Renderer) const
{
	FPoint Center{ GameConfig::WindowWidth * 0.5f, GameConfig::WindowHeight * 0.5 };

	Renderer->SetColor({ 30, 30, 30, 191 });
	Renderer->FillRect({ 0.0f, 0.0f, GameConfig::WindowWidth, GameConfig::WindowHeight });

	Renderer->SetFont(GameConfig::AncientFont, 200);
	Renderer->DrawText("Game Over", Center, EJustify::CenteredBottom, TextColor);

	Center.Y += 20.0f;
	Renderer->SetFont(GameConfig::AncientFont, 70);
	Renderer->DrawText("Score: " + std::to_string(AScoreManager::Get().GetCurrentScore()), Center, EJustify::CenteredTop, TextColor);

	Center.Y += 100.0f;
	Renderer->SetFont(GameConfig::OpenSansFont, 20);
	Renderer->DrawText("Press Enter to Exit", Center, EJustify::CenteredTop, TextColor);
}
