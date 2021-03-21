//
//  IScreenRequestSolver.h
//  Screen Request Solver Interfaces.
//
//  Created by Kirill Bravichev on 03/21/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "Screens/AScreenState.h"


struct IScreenRequestSolver
{
    virtual bool operator ()(const TSharedPtr<AScreenState>& Requester, int32 ScreenID, int32 Reason) const = 0;
};
