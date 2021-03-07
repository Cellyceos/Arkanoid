//
//  ArkanoidGame.h
//  Arkanoid Game.
//
//  Created by Kirill Bravichev on 02/27/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"

class ArkanoidGame
{
public:
	ArkanoidGame();
	~ArkanoidGame();

	bool Init();
	int32 Loop();

private:
	TSharedPtr<AWindowClass> MainWindow = nullptr;
	TSharedPtr<class AScreensManager> ScreensManager = nullptr;
};
