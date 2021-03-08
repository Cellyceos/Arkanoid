//
//  MainScreen.h
//  Main Screen State.
//
//  Created by Kirill Bravichev on 03/06/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "Screens/AScreenState.h"
#include "Game/GameConfig.h"


class AMainScreen : public AScreenState
{
public:
	AMainScreen(const TSharedPtr<class AScreensManager>& InOwner);

	virtual void Update(float DeltaTime) override;
	virtual void Draw(const TSharedPtr<ARendererClass>& Renderer) const override;

	virtual int32 GetId() const override { return static_cast<int32>(GameConfig::EScreenTypes::MainScreen); }

private:
	FColor FontColor{ 255, 255, 255, 255 };
	int8 Direction{ -2 };
};

