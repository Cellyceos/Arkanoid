//
//  PauseScreen.cpp
//  Pause Screen State.
//
//  Created by Kirill Bravichev on 03/06/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Screens/APauseScreen.h"


APauseScreen::APauseScreen(const TSharedPtr<class AScreensManager>& InOwner) : AScreenState(InOwner)
{

}

void APauseScreen::Draw(const TSharedPtr<ARendererClass>& Renderer) const
{
	const FPoint Center{ GameConfig::WindowWidth * 0.5f, GameConfig::WindowHeight * 0.5 };

	Renderer->SetColor({ 255, 255, 0, 255 });
	Renderer->DrawRect({ Center, { 5.0f, 5.0f } });

	Renderer->SetFont("Assets/Open Sans.ttf", 50);
	Renderer->DrawText("Game Pause", Center, ETextJustify::CenteredBottom, { 255, 255, 255, 255 });

	Renderer->SetFont("Assets/Open Sans.ttf", 15);
	Renderer->DrawText("Press Esc to Continue", Center, ETextJustify::CenteredTop, { 255, 255, 255, 255 });
}
