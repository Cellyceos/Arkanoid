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

	virtual bool Init(const FStringView Title, int32 Width, int32 Height) = 0;
	virtual void Show() = 0;
	virtual void Hide() = 0;

	virtual bool HandleEvents(TSharedPtr<class AInputManager> InputManager) = 0;

	virtual void PrepareDraw() = 0;
	virtual void FinishDraw() = 0;

	virtual const TSharedPtr<class IRenderer> GetRenderer() const { return Renderer; }

	virtual void SetBackgroundColor(const FColor& Color) { BackgroundColor = Color; }
	virtual FColor GetBackgroundColor() const { return BackgroundColor; }

	virtual bool HasFocus() const = 0;
	virtual void* GetNativeWindowHandle() const { return nullptr; }

protected:
	TSharedPtr<class IRenderer> Renderer = nullptr;

	FColor BackgroundColor;
};
