//
//  IInputManager.h
//  Base Wrapper Interface Class.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"

struct FKeyboardEvent
{
    uint8 State;
    bool IsRepeat;
    int32 Key;
};

struct FMouseMotionEvent
{
    uint32 State;
    int32 X;
    int32 Y;
    int32 Xrel;
    int32 Yrel;
};

struct FMouseButtonEvent
{
    uint8 Button;
    uint8 State;
    uint8 Clicks;
    int32 X;
    int32 Y;
};

class IInputManager
{
public:
	IInputManager() = default;
	virtual ~IInputManager() = default;

	virtual void KeyboardEvent(const FKeyboardEvent& Event) = 0;
	virtual void MouseButtonEvent(const FMouseButtonEvent& Event) = 0;
	virtual void MouseMotionEvent(const FMouseMotionEvent& Event) = 0;
};
