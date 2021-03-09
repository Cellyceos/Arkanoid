//
//  GameScreen.cpp
//  Game Screen State.
//
//  Created by Kirill Bravichev on 03/05/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Screens/AGameScreen.h"
#include "Screens/AScreensManager.h"

#include "AScoreManager.h"
#include "Objects/ALevel.h"

#include "SDL_keycode.h"


AGameScreen::AGameScreen(const TWeakPtr<class AScreensManager>& InOwner) : AScreenState(InOwner)
{
	CurrentLevel = std::make_shared<ALevel>();
}

AGameScreen::~AGameScreen()
{
	CurrentLevel = nullptr;
	SDL_Log("~AGameScreen\n");
}

void AGameScreen::Init()
{
	const float LevelWidth = (GameConfig::WindowWidth - GameConfig::BorderSize) * GameConfig::LevelRatio;
	CurrentLevel->SetRect({ GameConfig::BorderSize, GameConfig::BorderSize, LevelWidth,
		GameConfig::WindowHeight - 2.0f * GameConfig::BorderSize });

	Rect = { GameConfig::BorderSize + LevelWidth, GameConfig::BorderSize,
		(GameConfig::WindowWidth - 2.0f * GameConfig::BorderSize) - LevelWidth,
		GameConfig::WindowHeight - 2.0f * GameConfig::BorderSize };

	CurrentLevel->SetupPlayerInput(shared_from_this());

	BindKey(SDLK_ESCAPE, std::bind(&AGameScreen::Pause, this, _1));

	AScoreManager::Get().StartGame();
	CurrentLevel->StartGame();
}

void AGameScreen::OnWindowsLostFocus()
{
#ifdef NDEBUG
	RequestTransition(static_cast<int32>(GameConfig::EScreenTypes::PauseScreen)); 
#endif // NDEBUG
}

void AGameScreen::Pause(EInputEvent KeyEvent)
{
	if (KeyEvent == EInputEvent::Pressed)
	{
		RequestTransition(static_cast<int32>(GameConfig::EScreenTypes::PauseScreen));
	}
}

void AGameScreen::Update(float DeltaTime)
{
	if (CurrentLevel->GetLivesCount() > 0)
	{
		if (CurrentLevel->GetAliveBlocksCount() > 0)
		{
			CurrentLevel->Update(DeltaTime);
		}
		else if (!CurrentLevel->StartGame(CurrentLevel->GetCurrentLevel() + 1))
		{
			RequestTransition(static_cast<int32>(GameConfig::EScreenTypes::ScoreScreen));
		}
	}
	else
	{
		RequestTransition(static_cast<int32>(GameConfig::EScreenTypes::ScoreScreen));
	}
}

void AGameScreen::Draw(const TSharedPtr<ARendererClass>& Renderer) const
{
	CurrentLevel->Draw(Renderer);

#ifdef DEBUG_UI
	Renderer->SetColor({ 125, 125, 0, 255 });
	Renderer->DrawRect(Rect);
#endif // DEBUG_UI

	const float Halfheight = Rect.Height * 0.5f;
	FPoint Center{ Rect.X + Rect.Width * 0.5f, Rect.Y };
	Renderer->SetFont(GameConfig::AncientFont, 70);
	Renderer->DrawText("Arkanoid", Center, ETextJustify::CenteredTop, TextColor);

	Center.Y += Halfheight;
	Renderer->SetFont(GameConfig::OpenSansFont, 30);
	Renderer->DrawText("Lives: " + std::to_string(CurrentLevel->GetLivesCount()), Center, ETextJustify::CenteredTop, TextColor);

	const AScoreManager& ScoreManager = AScoreManager::Get();

	Center.Y -= 100.0f;
	Renderer->SetFont(GameConfig::AncientFont, 40);
	Renderer->DrawText("Score", Center, ETextJustify::CenteredBottom, TextColor);
	Renderer->SetFont(GameConfig::OpenSansFont, 30);
	Renderer->DrawText(std::to_string(ScoreManager.GetCurrentScore()), Center, ETextJustify::CenteredTop, TextColor);

	Center.Y -= 100.0f;
	Renderer->SetFont(GameConfig::AncientFont, 40);
	Renderer->DrawText("Hight Score", Center, ETextJustify::CenteredBottom, TextColor);
	Renderer->SetFont(GameConfig::OpenSansFont, 30);
	Renderer->DrawText(std::to_string(ScoreManager.GetHightScore()), Center, ETextJustify::CenteredTop, TextColor);

	Center.Y = Rect.Height + Rect.Y;
	Renderer->SetFont(GameConfig::OpenSansFont, 15);
	Renderer->DrawText("Space -- Release Ball", Center, ETextJustify::CenteredBottom, TextColor);
	Center.Y -= 20.0f;
	Renderer->DrawText("Arrow Right -- Move Right", Center, ETextJustify::CenteredBottom, TextColor);
	Center.Y -= 20.0f;
	Renderer->DrawText("Arrow Left -- Move Left", Center, ETextJustify::CenteredBottom, TextColor);
	Center.Y -= 20.0f;
	Renderer->DrawText("Esc -- Game Pause", Center, ETextJustify::CenteredBottom, TextColor);
}