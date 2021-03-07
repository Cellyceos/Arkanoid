//
//  AScreenState.h
//  User Interface Screen State for FSM.
//
//  Created by Kirill Bravichev on 03/05/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"

class AScreenState
{
public:
	AScreenState(const TSharedPtr<class AScreensManager>& InOwner) : Owner(InOwner) { }
	virtual ~AScreenState() = default;

	virtual void Enter();
	virtual void Exit();

	void SetupInputBindings();

	virtual void Update(float DeltaTime) { }
	virtual void Draw(const TSharedPtr<ARendererClass>& Renderer) const = 0;

	virtual bool ShouldDrawPrevScreen() const { return true; }
	virtual bool ShouldUpdatePrevStates() const { return false; }

	virtual void RequestTransition();

protected:
	TSharedPtr<class AScreensManager> Owner = nullptr;
};
