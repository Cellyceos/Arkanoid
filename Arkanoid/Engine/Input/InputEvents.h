//
//  InputEvents.h
//  Input Event Structures.
//
//  Created by Kirill Bravichev on 03/01/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"


enum class EInputState
{
    Released,
    Pressed
};

enum class EMouseButtonType
{
    ButtonLeft = 1,
    ButtonMiddle,
    ButtonRight,
    ButtonX1,
    ButtonX2
};

struct FKeyboardEvent
{
    EInputState State;
    bool IsRepeat;
    EInputKey Key;
};

struct FMouseMotionEvent
{
    uint32 State;
    int32 X;
    int32 Y;
    int32 dX;
    int32 dY;
};

struct FMouseButtonEvent
{
    EMouseButtonType Button;
    EInputState State;
    uint8 Clicks;
    int32 X;
    int32 Y;
};