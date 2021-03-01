//
//  Level.cpp
//  Manages all objects at the level.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Game/Level.h"
#include "Game/Platform.h"

#include "Engine/Interfaces/IRenderer.h"


ALevel::ALevel()
{
	Platform = std::make_unique<APlatform>();
}

ALevel::~ALevel()
{

}

void ALevel::SetupPlayerInput(const TSharedPtr<AInputManager>& InputManager)
{
	Platform->SetupPlayerInput(InputManager);
	Platform->SetOwner(weak_from_this());
}

void ALevel::Update(float DeltaTime)
{
	Platform->Update(DeltaTime);
}

void ALevel::Draw(const TSharedPtr<IRenderer>& Renderer)
{
	Platform->Draw(Renderer);
}
