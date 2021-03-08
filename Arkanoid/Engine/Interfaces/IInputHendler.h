//
//  IInputHendler.h
//  Input Handler Interfaces.
//
//  Created by Kirill Bravichev on 03/07/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"

class IInputHandler : public std::enable_shared_from_this<IInputHandler>
{
public:
	IInputHandler() = default;
	virtual ~IInputHandler() = default;

	virtual bool HasBindings() const = 0;
	virtual FInputDelegate GetDelegateBoundToKey(int32 KeyCode) const = 0;

	virtual void BindKey(int32 KeyCode, FInputDelegate Func) = 0;
};