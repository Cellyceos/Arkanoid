//
//  AGameUI.cpp
//  In Game User Interface Class.
//
//  Created by Kirill Bravichev on 03/07/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "UI/AGameUI.h"

void AGameUI::Update(float DeltaTime)
{

}

void AGameUI::Draw(const TSharedPtr<SDLRenderer>& Renderer) const
{
#ifdef DEBUG_UI
	Renderer->SetColor({ 125, 125, 0, 255 });
	Renderer->DrawRect({ Position, Size });
#endif // DEBUG_UI

	const FPoint Center { Position.X + Size.Width * 0.5f, Position.Y };
	Renderer->SetFont("Assets/Ancient Medium.ttf", 70);
	Renderer->DrawText("Arkanoid", Center, ETextJustify::CenteredTop, { 255, 255, 255, 255 });
}
