//
//  GameScreen.h
//  Game Screen State.
//
//  Created by Kirill Bravichev on 03/05/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "Screens/AScreenState.h"
#include "Game/GameConfig.h"


class AGameScreen : public AScreenState
{
public:
	AGameScreen(const TSharedPtr<class AScreensManager>& InOwner);
	virtual ~AGameScreen();

	virtual void Init() override;
	
	virtual void Update(float DeltaTime) override;
	virtual void Draw(const TSharedPtr<ARendererClass>& Renderer) const override;

	virtual bool ShouldDrawPrevScreen() const override { return false; }
	virtual int32 GetId() const override { return static_cast<int32>(GameConfig::EScreenTypes::GameScreen); }

protected:
	TUniquePtr<class ALevel> CurrentLevel = nullptr;
	TUniquePtr<class AGameUI> UI = nullptr;
	
	FColor TestColor;
};
