//
//  Level.cpp
//  Manages all objects at the level.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Game/Level.h"
#include "Game/Platform.h"

#include "Engine/Interfaces/IInputManager.h"
#include "Engine/Interfaces/IRenderer.h"


Level::Level()
{
	Player = MakeUnique<Platform>();
}

Level::~Level()
{

}

void Level::Init(SharedPtr<IInputManager> InputManager)
{

}

void Level::Update(float DeltaTime)
{
	Player->Update(DeltaTime);
}

void Level::Draw(SharedPtr<IRenderer> Renderer)
{
	Player->Draw(Renderer);
}
