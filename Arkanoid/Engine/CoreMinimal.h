//
//  CoreMinimal.h
//  Common data types and methods for project.
//
//  Created by Kirill Bravichev on 02/27/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include <cassert>

#include "BasicTypes.h"

#ifdef USE_SDL
#include "SDL/SDLWindow.h"
#include "SDL/SDLRenderer.h"
#include "SDL/SDLInputKeys.h"
#endif // USE_SDL

#include "Logging/Macros.h"
#include "Input/InputEvents.h"
