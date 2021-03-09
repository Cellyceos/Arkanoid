//
//  MainScreen.cpp
//  Main Screen State.
//
//  Created by Kirill Bravichev on 03/06/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Screens/AMainScreen.h"
#include "Screens/AScreensManager.h"

#include "SDL_events.h"

AMainScreen::AMainScreen(const TWeakPtr<class AScreensManager>& InOwner) : AScreenState(InOwner)
{

}

AMainScreen::~AMainScreen()
{
	SDL_Log("~AMainScreen\n");
}

void AMainScreen::Init()
{
	BindKey(SDLK_RETURN, std::bind(&AMainScreen::StartGame, this, _1));
	BindKey(SDLK_ESCAPE, std::bind(&AMainScreen::Quit, this, _1));
}

void AMainScreen::StartGame(EInputEvent KeyEvent)
{
	if (KeyEvent == EInputEvent::Pressed)
	{
		RequestTransition(static_cast<int32>(GameConfig::EScreenTypes::GameScreen));
	}
}

void AMainScreen::Quit(EInputEvent KeyEvent)
{
	if (KeyEvent == EInputEvent::Pressed)
	{
		if (!Owner.expired())
		{
			Owner.lock()->RequestToQuit();
		}
	}
}

void AMainScreen::Update(float DeltaTime)
{
	FontColor.Alpha += 2;
}

void AMainScreen::Draw(const TSharedPtr<ARendererClass>& Renderer) const
{
	const FPoint Center{ GameConfig::WindowWidth * 0.5f, GameConfig::WindowHeight * 0.5 };
	Renderer->SetFont(GameConfig::AncientFont, 170);
	Renderer->DrawText("Arkanoid", Center, ETextJustify::CenteredBottom, { 255, 255, 255, 255 });

	Renderer->SetFont(GameConfig::OpenSansFont, 30);
	Renderer->DrawText("Press Enter to Start", Center, ETextJustify::CenteredTop, FontColor);
}
