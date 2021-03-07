//
//  AObject.h
//  Base Class for All object in the game.
//
//  Created by Kirill Bravichev on 03/01/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"

class AObject : public std::enable_shared_from_this<AObject>
{
public:
	AObject() = default;
	virtual ~AObject() = default;

	virtual void SetupPlayerInput(const TSharedPtr<class IInputComponent>& InputComponent) { }

	virtual void Update(float DeltaTime) { }
	virtual void Draw(const TSharedPtr<class SDLRenderer>& Renderer) const = 0;

	virtual FRect GetRect() const { return {Position, Size}; }
	virtual void SetRect(const FRect& Rect) { Position = { Rect.X, Rect.Y }; Size = { Rect.Width, Rect.Height }; }

	virtual float GetWidth() const { return Size.Width; }
	virtual float GetHeight() const { return Size.Height; }

	virtual FSize GetSize() const { return Size; }
	virtual void SetSize(const FSize& NewSize) { Size = NewSize; }

	virtual void SetPosition(const FPoint& NewPos) { Position = NewPos; }
	virtual FPoint GetPosition() const { return Position; }

	virtual void SetCenterPoint(const FPoint& Point) { Position = { Point.X - Size.Width * 0.5f, Point.Y - Size.Height * 0.5f }; }
	virtual FPoint GetCenterPoint() const { return { Position.X + Size.Width * 0.5f, Position.Y + Size.Height * 0.5f }; }

protected:
	FPoint Position;
	FSize Size;
};
