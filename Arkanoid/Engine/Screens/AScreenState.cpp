//
//  AScreenState.cpp
//  User Interface Screen State for FSM.
//
//  Created by Kirill Bravichev on 03/05/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Screens/AScreenState.h"

void AScreenState::Enter()
{

}

void AScreenState::Exit()
{

}


/// Begin IInputHandler
void AScreenState::BindKey(int32 KeyCode, FInputDelegate Func)
{
	assert(KeyBindings.find(KeyCode) == KeyBindings.end());
	KeyBindings.insert(std::make_pair(KeyCode, std::move(Func)));
}

FInputDelegate AScreenState::GetDelegateBoundToKey(int32 KeyCode) const
{
	auto KeyIter = KeyBindings.find(KeyCode);
	if (KeyIter != KeyBindings.end())
	{
		return KeyIter->second;
	}

	return nullptr;
}
/// End IInputHandler
