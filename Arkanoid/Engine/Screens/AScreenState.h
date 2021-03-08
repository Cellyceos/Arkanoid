//
//  AScreenState.h
//  User Interface Screen State for FSM.
//
//  Created by Kirill Bravichev on 03/05/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IInputHendler.h"

class AScreenState : public IInputHandler
{
public:
	AScreenState(const TSharedPtr<class AScreensManager>& InOwner) : Owner(InOwner) { }
	virtual ~AScreenState() = default;

	virtual int32 GetId() const = 0;

	virtual void Init() { }
	virtual void Enter();
	virtual void Exit();

	virtual void Update(float DeltaTime) { }
	virtual void Draw(const TSharedPtr<ARendererClass>& Renderer) const = 0;

	virtual bool ShouldDrawPrevScreen() const { return true; }
	virtual bool ShouldUpdatePrevStates() const { return false; }
	virtual bool ShouldHandleInputsPrevStates() const { return false; }

	virtual void OnWindowsGainFocus() {}
	virtual void OnWindowsLostFocus() {}

protected:
	TSharedPtr<class AScreensManager> Owner = nullptr;

/// Begin IInputHandler
public:
	virtual bool HasBindings() const override { return KeyBindings.size() > 0; }
	virtual FInputDelegate GetDelegateBoundToKey(int32 KeyCode) const override;

protected:
	virtual void BindKey(int32 KeyCode, FInputDelegate Func) override;

private:
	TUnorderedMap<int32, FInputDelegate> KeyBindings;
/// End IInputHandler
};
