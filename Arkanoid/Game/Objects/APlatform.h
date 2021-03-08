//
//  Platform.h
//  Player controlled object.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "AObject.h"

class APlatform : public AObject
{
public:
	APlatform();
	virtual ~APlatform();

	virtual void SetupPlayerInput(const TSharedPtr<class IInputHandler>& InputComponent) override;

	virtual void Update(float DeltaTime) override;
	virtual void Draw(const TSharedPtr<class SDLRenderer>& Renderer) const override;

protected:
	void MoveLeft(EInputEvent KeyEvent);
	void MoveRight(EInputEvent KeyEvent);
	void ReleaseBall(EInputEvent KeyEvent);

private:
	float MoveSpeed = 0.0f;
	FColor GunColor;

	const float Speed{ 500.0f };
	const FColor BackGroundColor{ 120, 120, 120, 255 };
	const FColor ForegroundColor{ 150, 150, 150, 255 };

	bool HasGun = false;
};

