//
//  ArkanoidGame.h
//  Arkanoid Game.
//
//  Created by Kirill Bravichev on 02/27/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "ArkanoidGame.h"

#include "Game/Screens/FScreensCreator.h"

#include "Engine/FixedFrameRate.h"
#include "Engine/Screens/AScreensManager.h"

#include "Game/GameConfig.h"
#include "ALevelManager.h"

ArkanoidGame::ArkanoidGame()
{
	MainWindow = std::make_shared<AWindowClass>();
}

ArkanoidGame::~ArkanoidGame()
{
	SDL_Log("~ArkanoidGame\n");
	MainWindow->SetMessageHandler(nullptr);
	MainWindow = nullptr;

	ScreensManager = nullptr;
}

bool ArkanoidGame::Init()
{
	if (MainWindow->CreateWindow(GameConfig::WindowTitle, GameConfig::WindowWidth, GameConfig::WindowHeight))
	{
		ScreensManager = std::make_shared<AScreensManager>(std::make_shared<FScreensCreator>());
		ScreensManager->RequestScreenTransition(static_cast<int32>(GameConfig::EScreenTypes::MainScreen));

		MainWindow->SetMessageHandler(ScreensManager);

		// Load Levels
		ALevelManager::Get();

		MainWindow->Show();
		return true;
	}

	return false;
}

int32 ArkanoidGame::Loop()
{
	AFixedFrameRate FixedFrameRate(60ll);
	while (MainWindow->HandleEvents())
	{
		ScreensManager->Update(FixedFrameRate.GetDeltaTime());
		ScreensManager->Draw(MainWindow->GetRenderer());

		FixedFrameRate.WaitForFixedRate();
		printf("FPS: %lld\n", FixedFrameRate.GetCurrentFrameRate());
	}

	return 0;
}
