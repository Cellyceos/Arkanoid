//
//  Platform.cpp
//  Player controlled object.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Game/Platform.h"

#include "Engine/Input/InputManager.h"
#include "Engine/Interfaces/IRenderer.h"


APlatform::APlatform()
{
	Size = { 80.0f, 14.0f };
	Color = { 150, 150, 150, 255 };
	GunColor = { 80, 80, 80, 255 };
}

APlatform::~APlatform()
{

}

void APlatform::SetupPlayerInput(const TSharedPtr<AInputManager>& InputManager)
{
	InputManager->BindAxis("Move", std::bind(&APlatform::Move, this, _1));
	InputManager->BindAction("Release", EInputEvent::IE_Pressed, std::bind(&APlatform::ReleaseBall, this));
}

void APlatform::Move(float Direction)
{
	MoveSpeed = Direction * Speed;
}

void APlatform::ReleaseBall()
{

}

void APlatform::Update(float DeltaTime)
{
	if (MoveSpeed != 0.0f)
	{
		Position.X += MoveSpeed * DeltaTime;
	}
}

void APlatform::Draw(const TSharedPtr<IRenderer>& Renderer) const
{
	const float HalfHeight = Size.Height * 0.5f;
	const float HalfWidth = Size.Width * 0.5f;

	const FPoint& Center = GetCenterPoint();

	Renderer->SetColor({ 125, 125, 125, 255 });
	Renderer->FillCircle({ Position.X, Center.Y }, HalfHeight);
	Renderer->FillCircle({ Position.X + Size.Width - 1.0f, Center.Y }, HalfHeight);
	Renderer->FillRect({ Position, { Size.Width, Size.Height + 1.0f } });

	float Offset = 2.0f;
	Renderer->SetColor({ 150, 150, 150, 255 });
	Renderer->FillCircle({ Position.X, Center.Y }, HalfHeight - Offset);
	Renderer->FillCircle({ Position.X + Size.Width - 1.0f, Center.Y }, HalfHeight - Offset);
	Renderer->FillRect({ Position.X + Offset, Position.Y + Offset, Size.Width - 2.0f * Offset, Size.Height + 1.0f - 2.0f * Offset });

	if (HasGun)
	{
		const float GunPlatformWidth = Size.Width * 0.125f;
		const float GunPlatformHeight = Size.Height * 0.25f;
		const float HalfHeight = GunPlatformWidth * 0.5f;
		const float HalfWidth = GunPlatformHeight * 0.5f;

		Renderer->SetColor(GunColor);
		Renderer->FillRect({ Position.X, Position.Y - GunPlatformHeight, GunPlatformWidth, GunPlatformHeight });
		Renderer->FillRect({ Position.X + (HalfHeight - HalfWidth), Position.Y - GunPlatformWidth , GunPlatformHeight, GunPlatformWidth });

		Renderer->FillRect({ Position.X + Size.Width - GunPlatformWidth, Position.Y - GunPlatformHeight , GunPlatformWidth, GunPlatformHeight });
		Renderer->FillRect({ Position.X + Size.Width - (HalfHeight + HalfWidth), Position.Y - GunPlatformWidth , GunPlatformHeight, GunPlatformWidth });
	}
}
