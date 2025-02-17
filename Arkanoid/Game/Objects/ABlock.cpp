//
//  ABlock.cpp
//  Block object class.
//
//  Created by Kirill Bravichev on 03/02/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Objects/ABlock.h"


TFixedArray<const ABlock::FBlockSettings, static_cast<int32>(EBlockType::Count)> ABlock::BlockTypes =
{ {
	{},
	{ EBlockType::White, 1, 50, { 252, 252, 252, 255 } },
	{ EBlockType::Orange, 1, 60, { 252, 116, 96, 255 } },
	{ EBlockType::LightBlue, 1, 70, { 60, 188, 252, 255 } },
	{ EBlockType::Green, 1, 80, { 128, 208, 16, 255 } },
	{ EBlockType::Red, 1, 90, { 216, 40, 0, 255 } },
	{ EBlockType::Blue, 1, 100, { 0, 112, 236, 255 } },
	{ EBlockType::Pink, 1, 110, { 252, 116, 180, 255 } },
	{ EBlockType::Yellow, 1, 120, { 252, 152, 56, 255 } },
	{ EBlockType::Silver, 2, 50, { 148, 148, 148, 255 }, { 188, 188, 188, 255 } },
	{ EBlockType::Gold, 2, 0, { 200, 148, 20, 255 }, { 240, 188, 60, 255 } }
} };

ABlock::ABlock(EBlockType Type) : Settings(BlockTypes[static_cast<int32>(Type)]) 
{

}

ABlock::~ABlock()
{
	LOG("~ABlock\n");
}

void ABlock::OnCollisionEnter(const TSharedPtr<AObject>& Col)
{
	if (Settings.Type != EBlockType::Gold)
	{
		--Settings.Healh;
	}
}

void ABlock::Draw(const TSharedPtr<ARendererClass>& Renderer) const
{
	Renderer->SetColor(Settings.MainColor);
	Renderer->FillRect({ Position, Size });

	if (Settings.Healh > 1)
	{
		const float Offset = 3.0f;
		Renderer->SetColor(Settings.SecondColor);
		Renderer->FillRect({ Position.X + Offset, Position.Y + Offset, Size.Width - 2.0f * Offset, Size.Height - 2.0f * Offset });
	}
}
