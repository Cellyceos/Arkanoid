//
//  Platform.h
//  Player controlled object.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"

class Platform
{
public:
	Platform();
	~Platform();

	void Init(SharedPtr<class IInputManager> InputManager);
	void Update(float DeltaTime);
	void Draw(SharedPtr<class IRenderer> Renderer);

private:
	float Width = 80.0f;
	float Height = 14.0f;

	FPoint Center;

	FColor Color;
	FColor GunColor;

	bool HasGun = false;
};

