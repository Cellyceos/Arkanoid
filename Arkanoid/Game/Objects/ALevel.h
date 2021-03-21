//
//  Level.h
//  Manages all objects at the level.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "AObject.h"
#include "GameConfig.h"

class ALevel : public AObject
{
public:
	ALevel();
	virtual ~ALevel();

	bool StartGame(int32 InLevel = 1);

	virtual void SetupPlayerInput(const TSharedPtr<class IInputHandler>& InputComponent) override;

	virtual void Update(float DeltaTime) override;
	virtual void Draw(const TSharedPtr<ARendererClass>& Renderer) const override;

	virtual void SetRect(const FRect& Rect) override;

	virtual int32 GetCurrentLevel() const { return Level; }
	virtual int32 GetLivesCount() const { return CurrentLives; }
	virtual int32 GetAliveBlocksCount() const { return AliveBlocksCount; }

protected:
	TSharedPtr<class ABall> Ball;
	TSharedPtr<class APlatform> Platform;

	TFixedArray<TSharedPtr<class ABlock>, GameConfig::ColNum * GameConfig::RowNum> StaticObjects;

	void ReleaseBall(EInputState KeyEvent);

private:
	int32 AliveBlocksCount{ 0 };
	int32 CurrentLives{ 3 };
	int32 Level{ 1 };

	const FColor BorderColor{ 125, 125, 125, 255 };
	const float BorderSize{ 5.0f };

	void CheckCollision();
	void ShouldBeInside(const TSharedPtr<AObject>&);
};

