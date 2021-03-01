//
//  InputEvents.h
//  Input Event Structures.
//
//  Created by Kirill Bravichev on 03/01/2021.
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
