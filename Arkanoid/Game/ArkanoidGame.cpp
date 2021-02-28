//
//  ArkanoidGame.h
//  Arkanoid Game.
//
//  Created by Kirill Bravichev on 02/27/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "ArkanoidGame.h"
#include "SDL/SDLWindow.h"
#include "Game/Level.h"

ArkanoidGame::ArkanoidGame()
{
	MainWindow = MakeUnique<SDLWindow>();
	CurrentLevel = MakeUnique<Level>();
}

ArkanoidGame::~ArkanoidGame()
{
	CurrentLevel = nullptr;
	MainWindow = nullptr;
}

bool ArkanoidGame::Init()
{
	if (MainWindow->Init("Arkanoid Game", 800, 600))
	{
		CurrentLevel->Init(MainWindow->GetInputManager());
		MainWindow->Show();
		return true;
	}

	return false;
}

int32 ArkanoidGame::Exec()
{
	while (MainWindow->HandleEvents())
	{
		CurrentLevel->Update(0.0f);

		MainWindow->PrepareDraw();
		CurrentLevel->Draw(MainWindow->GetRenderer());
		MainWindow->FinishDraw();
	}

	return 0;
}
