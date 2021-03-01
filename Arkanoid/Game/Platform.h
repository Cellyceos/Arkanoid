//
//  Platform.h
//  Player controlled object.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Game/AObject.h"

class APlatform : public AObject
{
public:
	APlatform();
	virtual ~APlatform();

	virtual void SetupPlayerInput(const TSharedPtr<class AInputManager>& InputManager) override;

	virtual void Update(float DeltaTime) override;
	virtual void Draw(const TSharedPtr<class IRenderer>& Renderer) override;

	virtual void SetOwner(const TWeakPtr<AObject>& NewOwner) override;

protected:
	void Move(float Val);
	void ReleaseBall();

private:
	float MoveDirection = 0.0f;

	FColor Color;
	FColor GunColor;

	bool HasGun = false;
};

