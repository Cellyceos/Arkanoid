//
//  ArkanoidGame.h
//  Arkanoid Game.
//
//  Created by Kirill Bravichev on 02/27/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "ArkanoidGame.h"
#include "Game/Level.h"

#include "FixedFrameRate.h"
#include "Interfaces/IRenderer.h"
#include "Input/InputManager.h"

#if USE_SDL
#include "SDL/SDLWindow.h"
#endif

ArkanoidGame::ArkanoidGame()
{
	MainWindow = std::make_unique<AWindowClass>();
	CurrentLevel = std::make_shared<ALevel>();
	InputManager = std::make_shared<AInputManager>();
}

ArkanoidGame::~ArkanoidGame()
{
	CurrentLevel = nullptr;
	MainWindow = nullptr;
}

bool ArkanoidGame::Init()
{
	const int32 WindowWidth = 1024;
	const int32 WindowHeight = 768;

	if (MainWindow->Init("Arkanoid Game", WindowWidth, WindowHeight))
	{
		CurrentLevel->SetRect({ 10.0f, 10.0f, (WindowWidth - 10.0f) * (2.0f / 3.0f), WindowHeight - 20.0f });
		CurrentLevel->SetupPlayerInput(InputManager);
		MainWindow->Show();
		return true;
	}

	return false;
}

int32 ArkanoidGame::Exec()
{
	AFixedFrameRate FixedFrameRate(60ll);
	while (MainWindow->HandleEvents(InputManager))
	{
		CurrentLevel->Update(FixedFrameRate.GetDeltaTime());

		MainWindow->PrepareDraw();

		auto Renderer = MainWindow->GetRenderer();
		CurrentLevel->Draw(Renderer);

		MainWindow->FinishDraw();

		FixedFrameRate.WaitForFixedRate();
	}

	return 0;
}
