//
//  PauseScreen.h
//  Pause Screen State.
//
//  Created by Kirill Bravichev on 03/06/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "Screens/AScreenState.h"


class APauseScreen : public AScreenState
{
public:
	APauseScreen(const TSharedPtr<class AScreensManager>& InOwner);

	virtual void Init() override;
	virtual void Draw(const TSharedPtr<ARendererClass>& Renderer) const override;

	virtual int32 GetId() const override { return static_cast<int32>(GameConfig::EScreenTypes::PauseScreen); }
};

