//
//  ABlock.cpp
//  Block object class.
//
//  Created by Kirill Bravichev on 03/02/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Game/ABlock.h"

#include "Interfaces/IRenderer.h"

TUnorderedMap<EBlockType, ABlock::FBlockSettings> ABlock::BlockTypes
{
	{ EBlockType::White, { 1, { 252, 252, 252, 255 } } },
	{ EBlockType::Orange, { 1, { 252, 116, 96, 255 } } },
	{ EBlockType::LightBlue, { 1, { 60, 188, 252, 255 } } },
	{ EBlockType::Green, { 1, { 128, 208, 16, 255 } } },
	{ EBlockType::Red, { 1, { 216, 40, 0, 255 } } },
	{ EBlockType::Blue, { 1, { 0, 112, 236, 255 } } },
	{ EBlockType::Pink, { 1, { 252, 116, 180, 255 } } },
	{ EBlockType::Yellow, { 1, { 252, 152, 56, 255 } } },
	{ EBlockType::Silver, { 2, { 148, 148, 148, 255 }, { 188, 188, 188, 255 } } },
	{ EBlockType::Gold, { 2, { 200, 148, 20, 255 }, { 240, 188, 60, 255 } } }
};

ABlock::ABlock(EBlockType Type) : Settings(BlockTypes[Type]) { }

void ABlock::Update(float DeltaTime)
{

}

void ABlock::Draw(const TSharedPtr<class IRenderer>& Renderer) const
{
	Renderer->SetColor(Settings.MainColor);
	Renderer->FillRect({ Rect.X, Rect.Y, Rect.Width - 2.0f, Rect.Height - 2.0f });

	if (Settings.Healh > 1)
	{
		const float Offset = 3.0f;
		Renderer->SetColor(Settings.SecondColor);
		Renderer->FillRect({ Rect.X + Offset, Rect.Y + Offset, Rect.Width - 2.0f - 2.0f * Offset, Rect.Height - 2.0f - 2.0f * Offset });
	}
}
