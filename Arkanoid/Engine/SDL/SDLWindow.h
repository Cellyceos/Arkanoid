//
//  SDLWindow.h
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 02/27/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "BasicTypes.h"


class SDLWindow
{
public:
	SDLWindow();
	virtual ~SDLWindow();

	virtual bool CreateWindow(const FStringView& Title, int32 Width, int32 Height);
	virtual void Show();
	virtual void Hide();

	virtual int32 GetWidth() const;
	virtual int32 GetHeight() const;

	virtual bool HandleEvents();

	virtual bool HasFocus() const { return bHasFocus; }
	virtual void* GetNativeWindowHandle() const { return NativeWindow; }

	virtual TSharedPtr<class SDLRenderer> GetRenderer() { return Renderer; }
	virtual TSharedPtr<const class SDLRenderer> GetRenderer() const { return Renderer; }

	virtual void SetMessageHandler(const TSharedPtr<class IMessageHandler>& InMessageHandler) { MessageHandler = InMessageHandler; }

	static void SendQuitMessage();

private:
	TSharedPtr<class IMessageHandler> MessageHandler = nullptr;
	TSharedPtr<class SDLRenderer> Renderer = nullptr;

	struct SDL_Window* NativeWindow = nullptr;

	uint32 WindowID = 0;
	bool bHasFocus = false;
};

using AWindowClass = SDLWindow;
