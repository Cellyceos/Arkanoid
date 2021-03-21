//
//  FScreensCreator.h
//  Screen Creator for Arkanoud Game.
//
//  Created by Kirill Bravichev on 03/07/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "Interfaces/IScreensCreator.h"
#include "Game/GameConfig.h"


struct FScreensCreator : IScreensCreator
{
	FScreensCreator() : IScreensCreator(static_cast<int32>(GameConfig::EScreenTypes::MainScreen)) { }
	virtual ~FScreensCreator() = default;

	virtual int32 GetScreensCount() const override;
	virtual TSharedPtr<AScreenState> operator()(const TWeakPtr<class AScreensManager>& Owner, int32 StateID) const override;
};

