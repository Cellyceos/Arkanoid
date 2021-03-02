//
//  ABall.cpp
//  Ball object class.
//
//  Created by Kirill Bravichev on 03/02/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Game/ABall.h"

#include "Interfaces/IRenderer.h"

void ABall::Update(float DeltaTime)
{

}

void ABall::Draw(const TSharedPtr<IRenderer>& Renderer) const
{
	const float BallRadius = 10.0f;
	const FPoint Center{ 300.0f, 200.0f };

	Renderer->SetColor({ 100, 100, 100, 255 });
	Renderer->FillCircle({ Center.X, Center.Y }, BallRadius);

	Renderer->SetColor({ 125, 125, 125, 255 });
	Renderer->FillCircle({ Center.X - 3.0f, Center.Y - 3.0f }, BallRadius * 0.5f);

	Renderer->SetColor({ 150, 150, 150, 255 });
	Renderer->FillCircle({ Center.X - 5.0f, Center.Y - 4.0f }, BallRadius * 0.25f);
}
