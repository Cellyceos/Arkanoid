//
//  MainScreen.cpp
//  Main Screen State.
//
//  Created by Kirill Bravichev on 03/06/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Screens/AMainScreen.h"


AMainScreen::AMainScreen(const TSharedPtr<class AScreensManager>& InOwner) : AScreenState(InOwner)
{

}

void AMainScreen::Update(float DeltaTime)
{
	FontColor.Alpha += 2;
}

void AMainScreen::Draw(const TSharedPtr<ARendererClass>& Renderer) const
{
	const FPoint Center{ GameConfig::WindowWidth * 0.5f, GameConfig::WindowHeight * 0.5 };
	Renderer->SetFont("Assets/Ancient Medium.ttf", 170);
	Renderer->DrawText("Arkanoid", Center, ETextJustify::CenteredBottom, { 255, 255, 255, 255 });

	Renderer->SetColor({ 255, 255, 0, 255 });
	Renderer->DrawRect({ Center, { 5.0f, 5.0f } });

	Renderer->SetFont("Assets/Open Sans.ttf", 30);
	Renderer->DrawText("Press Enter to Start", Center, ETextJustify::CenteredTop, FontColor);
}
