//
//  Level.h
//  Manages all objects at the level.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include  "AObject.h"

class ALevel : public AObject
{
public:
	ALevel();
	virtual ~ALevel();

	void Init();

	virtual void SetupPlayerInput(const TSharedPtr<class IInputHandler>& InputComponent) override;

	virtual void Update(float DeltaTime) override;
	virtual void Draw(const TSharedPtr<class SDLRenderer>& Renderer) const override;

protected:
	static constexpr int64 ColNum = 11;
	static constexpr int64 RowNum = 28;

	TUniquePtr<class ABall> Ball;
	TUniquePtr<class APlatform> Platform;

	TFixedArray<TUniquePtr<class AObject>, ColNum * RowNum> StaticObjects;
	TArray<TUniquePtr<class AObject>> DynamicObjects;

	static TFixedArray<uint16, ColNum* RowNum> Level;
};

