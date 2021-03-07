//
//  GameScreen.h
//  Game Screen State.
//
//  Created by Kirill Bravichev on 03/05/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "Screens/AScreenState.h"


class AGameScreen : public AScreenState
{
public:
	AGameScreen(const TSharedPtr<class AScreensManager>& InOwner);
	virtual ~AGameScreen();

	virtual void Enter() override;
	
	virtual void Update(float DeltaTime) override;
	virtual void Draw(const TSharedPtr<ARendererClass>& Renderer) const override;

	virtual bool ShouldDrawPrevScreen() const override { return false; }

protected:
	TUniquePtr<class ALevel> CurrentLevel = nullptr;
	TUniquePtr<class AGameUI> UI = nullptr;
	
	FColor TestColor;
};

