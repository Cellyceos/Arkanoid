//
//  PauseScreen.cpp
//  Pause Screen State.
//
//  Created by Kirill Bravichev on 03/06/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Screens/APauseScreen.h"
#include "Screens/AScreensManager.h"

#include "SDL_events.h"

APauseScreen::APauseScreen(const TSharedPtr<class AScreensManager>& InOwner) : AScreenState(InOwner)
{

}

void APauseScreen::Init()
{
	BindKey(SDLK_ESCAPE, std::bind(&APauseScreen::Close, this, _1));
	BindKey(SDLK_RETURN, std::bind(&APauseScreen::Continue, this, _1));
}

void APauseScreen::Close(EInputEvent KeyEvent)
{
	if (KeyEvent == EInputEvent::Pressed)
	{
		Owner->RequestScreenTransition(static_cast<int32>(GameConfig::EScreenTypes::MainScreen));
	}
}

void APauseScreen::Continue(EInputEvent KeyEvent)
{
	if (KeyEvent == EInputEvent::Pressed)
	{
		Owner->RequestScreenTransition(static_cast<int32>(GameConfig::EScreenTypes::GameScreen));
	}
}

void APauseScreen::Draw(const TSharedPtr<ARendererClass>& Renderer) const
{
	const FPoint Center{ GameConfig::WindowWidth * 0.5f, GameConfig::WindowHeight * 0.5 };

	Renderer->SetFont("Assets/Open Sans.ttf", 50);
	Renderer->DrawText("Game Pause", Center, ETextJustify::CenteredBottom, { 255, 255, 255, 255 });

	Renderer->SetFont("Assets/Open Sans.ttf", 15);
	Renderer->DrawText("Press Enter to Continue", Center, ETextJustify::CenteredTop, { 255, 255, 255, 255 });
	Renderer->DrawText("Or Press Esc to Exit", {Center.X, Center.Y + 20.0f}, ETextJustify::CenteredTop, { 255, 255, 255, 255 });
}
