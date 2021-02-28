//
//  SDLInputManager.h
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IInputManager.h"

class SDLInputManager : public IInputManager
{
public:
	SDLInputManager();
	virtual ~SDLInputManager() = default;

	virtual void KeyboardEvent(const FKeyboardEvent& Event) override;
	virtual void MouseButtonEvent(const FMouseButtonEvent& Event) override;
	virtual void MouseMotionEvent(const FMouseMotionEvent& Event) override;
};
