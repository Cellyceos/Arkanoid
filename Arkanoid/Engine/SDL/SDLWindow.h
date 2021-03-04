//
//  SDLWindow.h
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 02/27/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/GenericWindow.h"

class SDLWindow : public AGenericWindow
{
public:
	SDLWindow();
	virtual ~SDLWindow();

	virtual bool Init(const FStringView Title, int32 Width, int32 Height) override;
	virtual void Show() override;
	virtual void Hide() override;

	virtual bool HandleEvents(const TSharedPtr<class AInputManager>& InputManager) override;

	virtual void PrepareDraw() override;
	virtual void FinishDraw() override;

	virtual bool HasFocus() const override { return bHasFocus; }
	virtual void* GetNativeWindowHandle() const override { return NativeWindow; }

private:
	struct SDL_Window* NativeWindow = nullptr;

	uint32 WindowID = 0;
	bool bHasFocus = false;
};

using AWindowClass = SDLWindow;
