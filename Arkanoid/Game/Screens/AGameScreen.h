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
	AGameScreen(const TWeakPtr<class AScreensManager>& InOwner);
	virtual ~AGameScreen();

	virtual void Init() override;
	virtual void Enter() override;

	virtual void Update(float DeltaTime) override;
	virtual void Draw(const TSharedPtr<ARendererClass>& Renderer) const override;

	virtual bool ShouldDrawPrevScreen() const override { return false; }
	virtual int32 GetId() const override { return static_cast<int32>(GameConfig::EScreenTypes::GameScreen); }

	virtual void OnWindowsLostFocus() override;

protected:
	TSharedPtr<class ALevel> CurrentLevel = nullptr;
	
private:
	FRect Rect;

	void Pause(EInputEvent KeyEvent);
};

