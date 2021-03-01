//
//  Level.h
//  Manages all objects at the level.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include  "Game/AObject.h"

class ALevel : public AObject
{
public:
	ALevel();
	virtual ~ALevel();

	virtual void SetupPlayerInput(const TSharedPtr<class AInputManager>& InputManager) override;

	virtual void Update(float DeltaTime) override;
	virtual void Draw(const TSharedPtr<class IRenderer>& Renderer) override;

protected:
	TUniquePtr<class APlatform> Platform;
};

