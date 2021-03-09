//
//  FScreensCreator.h
//  Screen Creator for Arkanoud Game.
//
//  Created by Kirill Bravichev on 03/07/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "Interfaces/IScreensCreator.h"


struct FScreensCreator : IScreensCreator
{
	virtual int32 GetScreensCount() const override;
	virtual TSharedPtr<AScreenState> operator()(const TWeakPtr<class AScreensManager>& Owner, int32 StateID) const override;
};

