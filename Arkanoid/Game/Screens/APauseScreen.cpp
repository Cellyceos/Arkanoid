//
//  PauseScreen.cpp
//  Pause Screen State.
//
//  Created by Kirill Bravichev on 03/06/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Screens/APauseScreen.h"
#include "Screens/AScreensManager.h"

#include "SDL_keycode.h"
#include "SDL_log.h"

APauseScreen::APauseScreen(const TWeakPtr<class AScreensManager>& InOwner) : AScreenState(InOwner)
{

}

APauseScreen::~APauseScreen()
{
	SDL_Log("~APauseScreen\n");
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
		RequestTransition(static_cast<int32>(GameConfig::EScreenTypes::MainScreen));
	}
}

void APauseScreen::Continue(EInputEvent KeyEvent)
{
	if (KeyEvent == EInputEvent::Pressed)
	{
		RequestTransition(static_cast<int32>(GameConfig::EScreenTypes::GameScreen));
	}
}

void APauseScreen::Draw(const TSharedPtr<ARendererClass>& Renderer) const
{
	FPoint Center{ GameConfig::WindowWidth * 0.5f, GameConfig::WindowHeight * 0.5 };

	Renderer->SetColor({ 30, 30, 30, 191 });
	Renderer->FillRect({ 0.0f, 0.0f, GameConfig::WindowWidth, GameConfig::WindowHeight });

	Renderer->SetFont(GameConfig::AncientFont, 200);
	Renderer->DrawText("Game Pause", Center, ETextJustify::CenteredBottom, TextColor);

	Renderer->SetFont(GameConfig::OpenSansFont, 20);
	Renderer->DrawText("Press Enter to Continue", Center, ETextJustify::CenteredTop, TextColor);

	Center.Y += 30.0f;
	Renderer->DrawText("Or Press Esc to Exit", Center, ETextJustify::CenteredTop, TextColor);
}
