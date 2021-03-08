//
//  IMessageHandler.h
//  Message Hendler Interfaces.
//
//  Created by Kirill Bravichev on 03/06/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"

class IMessageHandler
{
public:
    virtual void OnKeyDown(const struct SDL_KeyboardEvent& Event) = 0;
    virtual void OnKeyUp(const struct SDL_KeyboardEvent& Event) = 0;
    virtual void OnMouseButtonDown(const struct SDL_MouseButtonEvent& Event) = 0;
    virtual void OnMouseButtonUp(const struct SDL_MouseButtonEvent& Event) = 0;
    virtual void OnMouseMotion(const struct SDL_MouseMotionEvent& Event) = 0;

    virtual void OnWindowsFocusGained() = 0;
    virtual void OnWindowsFocusLost() = 0;
};
