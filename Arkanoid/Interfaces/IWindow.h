//
//  IWindow.h
//  Base Wrapper Interface Class.
//
//  Created by Kirill Bravichev on 02/27/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"

class IWindow
{
public:
	IWindow() = default;
	virtual ~IWindow() = default;

	virtual bool Init(const StringView Title, int32 Width, int32 Height) = 0;
	virtual void Show() = 0;

	virtual bool HandleEvents() = 0;

	virtual void PrepareUpdate() = 0;
	virtual void FinishUpdate() = 0;

	virtual const SharedPtr<class IRenderer> GetRenderer() const { return Renderer; }

	virtual void SetBackgroundColor(const FColor& Color) { BackgroundColor = Color; }
	virtual FColor GetBackgroundColor() const { return BackgroundColor; }

protected:
	SharedPtr<class IRenderer> Renderer = nullptr;

	FColor BackgroundColor;
};
