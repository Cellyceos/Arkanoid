//
//  Macros.h
//  Logging macros.
//
//  Created by Kirill Bravichev on 03/12/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once


#include "BasicTypes.h"
#include "SDL_log.h"


#ifdef _DEBUG
#define LOG(DebugStr, ...) SDL_Log(DebugStr, ##__VA_ARGS__)
#else
#define LOG(DebugStr, ...)
#endif

#ifdef _DEBUG
#define LOG_ERROR(DebugStr, ...) SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, DebugStr, ##__VA_ARGS__)
#else
#define LOG_ERROR(DebugStr, ...)
#endif

#ifdef _DEBUG
#define LOG_CRITICAL(DebugStr, ...) SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, DebugStr, ##__VA_ARGS__)
#else
#define LOG_CRITICAL(DebugStr, ...)
#endif
