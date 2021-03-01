//
//  Platform.cpp
//  Player controlled object.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Game/Platform.h"

#include "Engine/Interfaces/IInputManager.h"
#include "Engine/Interfaces/IRenderer.h"


Platform::Platform()
{
	Center = { 300, 500 };

	Color = { 150, 150, 150, 255 };
	GunColor = { 80, 80, 80, 255 };
}

Platform::~Platform()
{

}

void Platform::Init(TSharedPtr<IInputManager> InputManager)
{

}

void Platform::Update(float DeltaTime)
{

}

void Platform::Draw(TSharedPtr<IRenderer> Renderer)
{
	const float HalfHeight = Height * 0.5f;
	const float HalfWidth = Width * 0.5f;

	const float X = Center.X - HalfWidth;
	const float Y = Center.Y - HalfHeight;

	Renderer->SetColor(Color);
	Renderer->FillCircle({ X, Center.Y }, HalfHeight);
	Renderer->FillCircle({ X + Width, Center.Y }, HalfHeight);
	Renderer->FillRect({ X, Y, Width, Height + 1.0f });

	if (HasGun)
	{
		const float GunPlatformWidth = Width * 0.125f;
		const float GunPlatformHeight = Height * 0.25f;
		const float HalfHeight = GunPlatformWidth * 0.5f;
		const float HalfWidth = GunPlatformHeight * 0.5f;

		Renderer->SetColor(GunColor);
		Renderer->FillRect({ X, Y - GunPlatformHeight, GunPlatformWidth, GunPlatformHeight });
		Renderer->FillRect({ X + (HalfHeight - HalfWidth), Y - GunPlatformWidth, GunPlatformHeight, GunPlatformWidth });

		Renderer->FillRect({ X + Width - GunPlatformWidth, Y - GunPlatformHeight, GunPlatformWidth, GunPlatformHeight });
		Renderer->FillRect({ X + Width - (HalfHeight + HalfWidth), Y - GunPlatformWidth, GunPlatformHeight, GunPlatformWidth });
	}
}
