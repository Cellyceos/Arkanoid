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


ArkanoidGame::ArkanoidGame()
{
	MainWindow = std::make_shared<AWindowClass>();
}

ArkanoidGame::~ArkanoidGame()
{
	MainWindow = nullptr;
}

bool ArkanoidGame::Init()
{
	if (MainWindow->CreateWindow(GameConfig::WindowTitle, GameConfig::WindowWidth, GameConfig::WindowHeight))
	{
		ScreensManager = std::make_shared<AScreensManager>(FScreensCreator());
		MainWindow->SetMessageHandler(ScreensManager);

		ScreensManager->Init();
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
	}

	return 0;
}
