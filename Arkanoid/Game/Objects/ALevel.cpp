//
//  Level.cpp
//  Manages all objects at the level.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Objects/ALevel.h"
#include "Objects/ABall.h"
#include "Objects/ABlock.h"
#include "Objects/APlatform.h"


TFixedArray<uint16, ALevel::ColNum * ALevel::RowNum> ALevel::Level{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
};


ALevel::ALevel()
{
	Platform = std::make_unique<APlatform>();
	Ball = std::make_unique<ABall>();
}

ALevel::~ALevel()
{

}

void ALevel::Init()
{
	//Platform->SetupPlayerInput(InputManager);
	Platform->SetCenterPoint({ Position.X + Size.Width * 0.5f, Size.Height - Platform->GetHeight() });
	Ball->SetCenterPoint({ Position.X + Size.Width * 0.5f, Size.Height - Platform->GetHeight() - Ball->GetHeight() });

	const float X = Position.X + GameConfig::BorderSize;
	const float Y = Position.Y + GameConfig::BorderSize;
	const float BrickWidth = (Size.Width - 2.0f * GameConfig::BorderSize) / ColNum;
	const float BrickHeight = (Size.Height - 2.0f * GameConfig::BorderSize) / RowNum;

	for (uint64 Idx = 0ll; Idx < Level.size(); Idx++)
	{
		const EBlockType BlockType = static_cast<EBlockType>(Level[Idx]);
		if (BlockType != EBlockType::Unknown)
		{
			auto Block = std::make_unique<ABlock>(BlockType);
			Block->SetRect({ X + Idx % ColNum * BrickWidth, Y + Idx / ColNum * BrickHeight, BrickWidth, BrickHeight });
			StaticObjects[Idx] = std::move(Block);
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

void ALevel::Draw(const TSharedPtr<SDLRenderer>& Renderer) const
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
	Renderer->DrawRect({Position, Size});
}
