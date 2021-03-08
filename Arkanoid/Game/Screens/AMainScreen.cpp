//
//  MainScreen.cpp
//  Main Screen State.
//
//  Created by Kirill Bravichev on 03/06/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Screens/AMainScreen.h"
#include "Screens/AScreensManager.h"

#include "SDL_keycode.h"

AMainScreen::AMainScreen(const TSharedPtr<class AScreensManager>& InOwner) : AScreenState(InOwner)
{

}
void AMainScreen::Init()
{
	BindKey(SDLK_RETURN, std::bind(&AMainScreen::Close, this, _1));
}

void AMainScreen::Close(EInputEvent KeyEvent)
{
	if (KeyEvent == EInputEvent::Pressed)
	{
		Owner->RequestScreenTransition(static_cast<int32>(GameConfig::EScreenTypes::GameScreen));
	}
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

	Renderer->SetFont("Assets/Open Sans.ttf", 30);
	Renderer->DrawText("Press Enter to Start", Center, ETextJustify::CenteredTop, FontColor);
}
