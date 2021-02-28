//
//  Level.h
//  Manages all objects at the level.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"

class Level
{
public:
	Level();
	~Level();

	void Init(SharedPtr<class IInputManager> InputManager);
	void Update(float DeltaTime);
	void Draw(SharedPtr<class IRenderer> Renderer);

private:
	UniquePtr<class Platform> Player = nullptr;
};

