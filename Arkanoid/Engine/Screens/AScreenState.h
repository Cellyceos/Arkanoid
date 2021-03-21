//
//  AScreenState.h
//  User Interface Screen State for FSM.
//
//  Created by Kirill Bravichev on 03/05/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "BasicTypes.h"
#include "Interfaces/IInputHendler.h"

class AScreenState : public IInputHandler, public std::enable_shared_from_this<AScreenState>
{
public:
	AScreenState(const TWeakPtr<class AScreensManager>& InOwner) : Owner(InOwner) { }
	virtual ~AScreenState() = default;

	virtual int32 GetId() const = 0;

	virtual void Init() { }

	virtual void Update(float DeltaTime) { }
	virtual void Draw(const TSharedPtr<ARendererClass>& Renderer) const = 0;

	virtual bool ShouldDrawPrevScreen() const { return true; }
	virtual bool ShouldUpdatePrevStates() const { return false; }
	virtual bool ShouldHandleInputsPrevStates() const { return false; }

	virtual void OnWindowsGainFocus() {}
	virtual void OnWindowsLostFocus() {}

	virtual void RequestTransition(int32 ScreenId, int32 Reason);

protected:
	TWeakPtr<class AScreensManager> Owner;
	const FColor TextColor{ 255, 255, 255, 255 };

/// Begin IInputHandler
public:
	virtual bool HasBindings() const override { return KeyBindings.size() > 0; }
	virtual FInputDelegate GetDelegateBoundToKey(EInputKey KeyCode) const override;

protected:
	virtual void BindKey(EInputKey KeyCode, FInputDelegate Func) override;

private:
	TUnorderedMap<EInputKey, FInputDelegate> KeyBindings;
/// End IInputHandler
};
