//
//  IMessageHandler.h
//  Message Hendler Interfaces.
//
//  Created by Kirill Bravichev on 03/06/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "Input/InputEvents.h"


class IMessageHandler
{
public:
    virtual void OnKeyDown(const FKeyboardEvent& Event) = 0;
    virtual void OnKeyUp(const FKeyboardEvent& Event) = 0;
    virtual void OnMouseButtonDown(const FMouseButtonEvent& Event) = 0;
    virtual void OnMouseButtonUp(const FMouseButtonEvent& Event) = 0;
    virtual void OnMouseMotion(const FMouseMotionEvent& Event) = 0;

    virtual void OnWindowsFocusGained() = 0;
    virtual void OnWindowsFocusLost() = 0;
};
