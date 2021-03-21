//
//  IScreensCreator.h
//  Screen Creator Interfaces.
//
//  Created by Kirill Bravichev on 03/07/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "Screens/AScreenState.h"


struct IScreensCreator
{
    static constexpr int32 InvalidScreenId{ -1 };
    const int32 DefaultScreenId{ 0 };

    IScreensCreator(int32 DefaultId) : DefaultScreenId{DefaultId} { }
    virtual ~IScreensCreator() = default;

    virtual int32 GetScreensCount() const = 0;
    virtual TSharedPtr<AScreenState> operator ()(const TWeakPtr<class AScreensManager>& Owner, int32 StateID) const = 0;
};
