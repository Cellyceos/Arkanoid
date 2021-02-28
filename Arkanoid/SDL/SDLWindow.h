//
//  SDLWindow.h
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 02/27/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IWindow.h"

class SDLWindow : public IWindow
{
public:
	SDLWindow();
	~SDLWindow();

	virtual bool Init(const StringView Title, int32 Width, int32 Height) override;
	virtual void Deinit() override;
	virtual void Show() override;

	virtual bool HandleEvents() override;

private:
	struct SDL_Window* Window = nullptr;
};
