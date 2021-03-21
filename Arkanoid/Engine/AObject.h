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

	virtual void SetupPlayerInput(const TSharedPtr<class IInputHandler>& InputComponent) { }

	virtual void Update(float DeltaTime) { }
	virtual void Draw(const TSharedPtr<ARendererClass>& Renderer) const = 0;

	virtual FRect GetRect() const { return { Position, Size }; }
	virtual void SetRect(const FRect& Rect);

	virtual float GetWidth() const { return Size.Width; }
	virtual float GetHeight() const { return Size.Height; }

	virtual FSize GetSize() const { return Size; }
	virtual void SetSize(const FSize& NewSize);

	virtual void SetPosition(const FPoint& NewPos);
	virtual FPoint GetPosition() const { return Position; }

	virtual void OnCollisionEnter(const TSharedPtr<AObject>& Col) {}

	virtual void SetCenterPoint(const FPoint& Point);
	virtual FPoint GetCenterPoint() const { return Aabb.Center; }

	virtual FAABB GetAABB() const { return Aabb; }

	virtual bool ShouldBeDestroyed() const { return false; }

protected:
	FPoint Position;
	FSize Size;
	FAABB Aabb;
};
