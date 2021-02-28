//
//  IRenderer.h
//  Base Wrapper Interface Class.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"

class IRenderer
{
public:
	IRenderer() = default;
	virtual ~IRenderer() = default;

	virtual void Clear(const FColor& Color) = 0;
	virtual void Present() = 0;

	virtual void SetColor(const FColor& Color) = 0;

	virtual void DrawRect(const FRect& Rect) = 0;
	virtual void FillRect(const FRect& Rect) = 0;

	virtual void DrawCircle(const FPoint& Center, int32 Radius) = 0;
	virtual void FillCircle(const FPoint& Center, int32 Radius) = 0;

	virtual void* GetNativeRenderer() const { return nullptr; }
};
