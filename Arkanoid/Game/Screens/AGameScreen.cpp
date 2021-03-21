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


AGameScreen::AGameScreen(const TWeakPtr<class AScreensManager>& InOwner) : AScreenState(InOwner)
{
	CurrentLevel = std::make_shared<ALevel>();
}

AGameScreen::~AGameScreen()
{
	CurrentLevel = nullptr;
	LOG("~AGameScreen\n");
}

void AGameScreen::Init()
{
	const float LevelWidth = (GameConfig::WindowWidth - GameConfig::BorderSize) * GameConfig::LevelRatio;
	CurrentLevel->SetRect({ GameConfig::BorderSize, GameConfig::BorderSize, LevelWidth,
		GameConfig::WindowHeight - 2.0f * GameConfig::BorderSize });

	UIRect = { GameConfig::BorderSize + LevelWidth, GameConfig::BorderSize,
		(GameConfig::WindowWidth - 2.0f * GameConfig::BorderSize) - LevelWidth,
		GameConfig::WindowHeight - 2.0f * GameConfig::BorderSize };

	CurrentLevel->SetupPlayerInput(shared_from_this());

	BindKey(EInputKey::Escape, std::bind(&AGameScreen::Pause, this, _1));

	AScoreManager::Get().StartGame();
	CurrentLevel->StartGame();
}

void AGameScreen::OnWindowsLostFocus()
{
#ifdef NDEBUG
	RequestTransition(static_cast<int32>(GameConfig::EScreenTypes::PauseScreen), static_cast<int32>(GameConfig::EScreenRequestReason::Force));
#endif // NDEBUG
}

void AGameScreen::Pause(EInputState KeyEvent)
{
	if (KeyEvent == EInputState::Pressed)
	{
		RequestTransition(static_cast<int32>(GameConfig::EScreenTypes::PauseScreen), static_cast<int32>(GameConfig::EScreenRequestReason::Default));
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
			RequestTransition(static_cast<int32>(GameConfig::EScreenTypes::ScoreScreen), static_cast<int32>(GameConfig::EScreenRequestReason::Default));
		}
	}
	else
	{
		RequestTransition(static_cast<int32>(GameConfig::EScreenTypes::ScoreScreen), static_cast<int32>(GameConfig::EScreenRequestReason::Default));
	}
}

void AGameScreen::Draw(const TSharedPtr<ARendererClass>& Renderer) const
{
	CurrentLevel->Draw(Renderer);

#ifdef DEBUG_UI
	Renderer->SetColor({ 125, 125, 0, 255 });
	Renderer->DrawRect(Rect);
#endif // DEBUG_UI

	const float Halfheight = UIRect.Height * 0.5f;
	FPoint Center{ UIRect.X + UIRect.Width * 0.5f, UIRect.Y };
	Renderer->SetFont(GameConfig::AncientFont, 70);
	Renderer->DrawText("Arkanoid", Center, EJustify::CenteredTop, TextColor);

	Center.Y += Halfheight;
	Renderer->SetFont(GameConfig::OpenSansFont, 30);
	Renderer->DrawText("Lives: " + std::to_string(CurrentLevel->GetLivesCount()), Center, EJustify::CenteredTop, TextColor);

	const AScoreManager& ScoreManager = AScoreManager::Get();

	Center.Y -= 100.0f;
	Renderer->SetFont(GameConfig::AncientFont, 40);
	Renderer->DrawText("Score", Center, EJustify::CenteredBottom, TextColor);
	Renderer->SetFont(GameConfig::OpenSansFont, 30);
	Renderer->DrawText(std::to_string(ScoreManager.GetCurrentScore()), Center, EJustify::CenteredTop, TextColor);

	Center.Y -= 100.0f;
	Renderer->SetFont(GameConfig::AncientFont, 40);
	Renderer->DrawText("Hight Score", Center, EJustify::CenteredBottom, TextColor);
	Renderer->SetFont(GameConfig::OpenSansFont, 30);
	Renderer->DrawText(std::to_string(ScoreManager.GetHightScore()), Center, EJustify::CenteredTop, TextColor);

	Center.Y = UIRect.Height + UIRect.Y;
	Renderer->SetFont(GameConfig::OpenSansFont, 15);
	Renderer->DrawText("Space -- Release Ball", Center, EJustify::CenteredBottom, TextColor);
	Center.Y -= 20.0f;
	Renderer->DrawText("Arrow Right -- Move Right", Center, EJustify::CenteredBottom, TextColor);
	Center.Y -= 20.0f;
	Renderer->DrawText("Arrow Left -- Move Left", Center, EJustify::CenteredBottom, TextColor);
	Center.Y -= 20.0f;
	Renderer->DrawText("Esc -- Game Pause", Center, EJustify::CenteredBottom, TextColor);
}