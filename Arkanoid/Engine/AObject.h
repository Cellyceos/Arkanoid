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

	virtual void SetupPlayerInput(const TSharedPtr<class AInputManager>& InputManager) { }

	virtual void Update(float DeltaTime) { }
	virtual void Draw(const TSharedPtr<class IRenderer>& Renderer) const = 0;

	virtual FRect GetRect() const { return Rect; }
	virtual void SetRect(const FRect& NewRect) { Rect = NewRect; }

	virtual FSize GetSize() const { return { GetWidth(), GetHeight() }; }

	virtual float GetWidth() const { return Rect.Width; }
	virtual float GetHeight() const { return Rect.Height; }

	virtual void SetPosition(const FPoint& NewPos) { Rect.X = NewPos.X; Rect.Y = NewPos.Y; }
	virtual FPoint GetPosition() const { return { Rect.X, Rect.Y }; }

	virtual void SetCenterPoint(const FPoint& Point) { Rect.X = Point.X - Rect.Width * 0.5f; Rect.Y = Point.Y - Rect.Height * 0.5f; }
	virtual FPoint GetCenterPoint() const { return { Rect.X + Rect.Width * 0.5f, Rect.Y + Rect.Height * 0.5f }; }


protected:
	FRect Rect;
};
