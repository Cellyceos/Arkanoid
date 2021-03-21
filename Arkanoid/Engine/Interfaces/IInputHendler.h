//
//  IInputHendler.h
//  Input Handler Interfaces.
//
//  Created by Kirill Bravichev on 03/07/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "BasicTypes.h"
#include "Input/InputEvents.h"


using FInputDelegate = TFunction<void(EInputState)>;
class IInputHandler
{
public:
	IInputHandler() = default;
	virtual ~IInputHandler() = default;

	virtual bool HasBindings() const = 0;
	virtual FInputDelegate GetDelegateBoundToKey(EInputKey KeyCode) const = 0;

	virtual void BindKey(EInputKey KeyCode, FInputDelegate Func) = 0;
};