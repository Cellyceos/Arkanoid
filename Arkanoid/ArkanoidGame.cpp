//
//  ArkanoidGame.h
//  Arkanoid Game.
//
//  Created by Kirill Bravichev on 02/27/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "ArkanoidGame.h"
#include "SDL/SDLWindow.h"

ArkanoidGame::ArkanoidGame()
{
	MainWindow = MakeUnique<SDLWindow>();
}

ArkanoidGame::~ArkanoidGame()
{
}

bool ArkanoidGame::Init()
{
	if (MainWindow->Init("Arkanoid Game", 800, 600))
	{
		MainWindow->Show();
		return true;
	}

	return false;
}

int32 ArkanoidGame::Exec()
{
	while (MainWindow->HandleEvents())
	{

	}

	return 0;
}
