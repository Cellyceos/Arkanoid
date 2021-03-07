//
//  IScreensCreator.h
//  Screen Creator Interfaces.
//
//  Created by Kirill Bravichev on 03/07/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Screens/AScreenState.h"

struct IScreensCreator
{
    virtual TUniquePtr<AScreenState> operator ()(const TSharedPtr<class AScreensManager>& Owner, int32 StateID) const { return nullptr; }
};
