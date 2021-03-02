//
//  Level.cpp
//  Manages all objects at the level.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Game/Level.h"
#include "Game/ABall.h"
#include "Game/ABlock.h"
#include "Game/Platform.h"

#include "Engine/Interfaces/IRenderer.h"


ALevel::ALevel()
{
	Platform = std::make_unique<APlatform>();
	Ball = std::make_unique<ABall>();
}

ALevel::~ALevel()
{

}

void ALevel::SetupPlayerInput(const TSharedPtr<AInputManager>& InputManager)
{
	Platform->SetupPlayerInput(InputManager);
	Platform->SetOwner(weak_from_this());

	const float X = Rect.X + 10.0f;
	const float Y = Rect.Y + 10.0f;
	const float BrickWidth = (Rect.Width - 20.0f) / 11.0f;
	const float BrickHeight = (Rect.Height - 20.0f) / 28.0f;

	for (int64 CollIdx = 0ll; CollIdx < ColNum; CollIdx++)
	{
		for (int64 RowIdx = 0ll; RowIdx < RowNum; RowIdx++)
		{
			auto Block = std::make_unique<ABlock>(EBlockType::Silver);
			Block->SetRect({ X + CollIdx * BrickWidth, Y + RowIdx * BrickHeight, BrickWidth, BrickHeight });
			Block->SetOwner(weak_from_this());

			StaticObjects[CollIdx * RowNum + RowIdx] = std::move(Block);
		}
	}
}

void ALevel::Update(float DeltaTime)
{
	for (const auto& Obj : StaticObjects)
	{
		if (Obj)
		{
			Obj->Update(DeltaTime);
		}
	}

	for (const auto& Obj : DynamicObjects)
	{
		if (Obj)
		{
			Obj->Update(DeltaTime);
		}
	}

	Platform->Update(DeltaTime);
}

void ALevel::Draw(const TSharedPtr<IRenderer>& Renderer) const
{
	for (const auto& Obj : StaticObjects)
	{
		if (Obj)
		{
			Obj->Draw(Renderer);
		}
	}

	for (const auto& Obj : DynamicObjects)
	{
		if (Obj)
		{
			Obj->Draw(Renderer);
		}
	}

	Ball->Draw(Renderer);
	Platform->Draw(Renderer);

	Renderer->SetColor({ 255, 0, 0, 255 });
	Renderer->DrawRect(Rect);

}
