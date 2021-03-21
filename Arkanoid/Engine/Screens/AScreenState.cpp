//
//  AScreenState.cpp
//  User Interface Screen State for FSM.
//
//  Created by Kirill Bravichev on 03/05/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Screens/AScreenState.h"
#include "Screens/AScreensManager.h"


void AScreenState::RequestTransition(int32 ScreenId, int32 Reason)
{
	if (!Owner.expired())
	{
		Owner.lock()->RequestScreenTransition(shared_from_this(), ScreenId, Reason);
	}
}

/// Begin IInputHandler
void AScreenState::BindKey(EInputKey KeyCode, FInputDelegate Func)
{
	assert(KeyBindings.find(KeyCode) == KeyBindings.end());
	KeyBindings.insert(std::make_pair(KeyCode, std::move(Func)));
}

FInputDelegate AScreenState::GetDelegateBoundToKey(EInputKey KeyCode) const
{
	auto KeyIter = KeyBindings.find(KeyCode);
	if (KeyIter != KeyBindings.end())
	{
		return KeyIter->second;
	}

	return nullptr;
}
/// End IInputHandler
