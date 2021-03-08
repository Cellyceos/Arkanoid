//
//  GameScreen.cpp
//  Game Screen State.
//
//  Created by Kirill Bravichev on 03/05/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Screens/AGameScreen.h"

#include "Objects/ALevel.h"
#include "UI/AGameUI.h"


AGameScreen::AGameScreen(const TSharedPtr<class AScreensManager>& InOwner) : AScreenState(InOwner)
{
	CurrentLevel = std::make_unique<ALevel>();
	UI = std::make_unique<AGameUI>();
}

AGameScreen::~AGameScreen()
{
	CurrentLevel = nullptr;
}

void AGameScreen::Init()
{
	CurrentLevel->SetRect({ GameConfig::BorderSize, GameConfig::BorderSize,
		(GameConfig::WindowWidth - GameConfig::BorderSize) * GameConfig::LevelRatio,
		GameConfig::WindowHeight - 2.0f * GameConfig::BorderSize });

	UI->SetRect({ 2.0f * GameConfig::BorderSize + CurrentLevel->GetWidth(),
		GameConfig::BorderSize,
		(GameConfig::WindowWidth - 3.0f * GameConfig::BorderSize) - CurrentLevel->GetWidth(),
		GameConfig::WindowHeight - 2.0f * GameConfig::BorderSize });

	CurrentLevel->Init();
}

void AGameScreen::Update(float DeltaTime)
{
	CurrentLevel->Update(DeltaTime);
}

void AGameScreen::Draw(const TSharedPtr<ARendererClass>& Renderer) const
{
	Renderer->SetColor({ 0, 255, 0, 255 });
	Renderer->DrawRect({ GameConfig::BorderSize, GameConfig::BorderSize,
		GameConfig::WindowWidth - 2.0f * GameConfig::BorderSize,
		GameConfig::WindowHeight - 2.0f * GameConfig::BorderSize });

	CurrentLevel->Draw(Renderer);
	UI->Draw(Renderer);
}