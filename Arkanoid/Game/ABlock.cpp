//
//  ABlock.cpp
//  Block object class.
//
//  Created by Kirill Bravichev on 03/02/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Game/ABlock.h"

#include "Interfaces/IRenderer.h"

void ABlock::Update(float DeltaTime)
{

}

void ABlock::Draw(const TSharedPtr<class IRenderer>& Renderer) const
{
	Renderer->SetColor({ 5, 150, 50, 255 });
	Renderer->FillRect({ Rect.X, Rect.Y, Rect.Width - 2.0f, Rect.Height - 2.0f });

	float Offset = 3.0f;
	Renderer->SetColor({ 5, 175, 50, 255 });
	Renderer->FillRect({ Rect.X + Offset, Rect.Y + Offset, Rect.Width - 2.0f - 2.0f * Offset, Rect.Height - 2.0f - 2.0f * Offset });

	Offset = 6.0f;
	Renderer->SetColor({ 5, 200, 50, 255 });
	Renderer->FillRect({ Rect.X + Offset, Rect.Y + Offset, Rect.Width - 2.0f - 2.0f * Offset, Rect.Height - 2.0f - 2.0f * Offset });

	Offset = 9.0f;
	Renderer->SetColor({ 5, 225, 50, 255 });
	Renderer->FillRect({ Rect.X + Offset, Rect.Y + Offset, Rect.Width - 2.0f - 2.0f * Offset, Rect.Height - 2.0f - 2.0f * Offset });
}
