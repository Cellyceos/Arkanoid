//
//  ScoreScreen.h
//  Score Screen State.
//
//  Created by Kirill Bravichev on 03/06/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "Screens/AScreenState.h"


class AScoreScreen : public AScreenState
{
public:
	AScoreScreen(const TSharedPtr<class AScreensManager>& InOwner);

	virtual void Draw(const TSharedPtr<ARendererClass>& Renderer) const override;
};

