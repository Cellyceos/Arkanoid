//
//  InputManager.h
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"

enum class EInputEvent
{
	IE_Pressed = 0,
	IE_Released = 1,
	IE_Repeat = 2,
	IE_DoubleClick = 3,
	IE_Axis = 4,
	IE_MAX = 5,
};

struct FInputBinding
{
	/** Whether the binding should consume the input or allow it to pass to another component */
	uint8 bConsumeInput : 1;

	/** Whether the binding should execute while paused */
	uint8 bExecuteWhenPaused : 1;

	FInputBinding()
		: bConsumeInput(true)
		, bExecuteWhenPaused(false)
	{}
};

/** Binds a delegate to an axis mapping. */
struct FInputAxisBinding : public FInputBinding
{
	/** The axis mapping being bound to. */
	FString AxisName;

	/**
	 * The delegate bound to the axis.
	 * It will be called each frame that the input component is in the input stack
	 * regardless of whether the value is non-zero or has changed.
	 */
	TFunction<void(float)> AxisDelegate;

	/**
	 * The value of the axis as calculated during the most recent UPlayerInput::ProcessInputStack
	 * if the InputComponent was in the stack, otherwise all values should be 0.
	 */
	float AxisValue = 0.0f;

	FInputAxisBinding(const FString& InAxisName)
		: FInputBinding()
		, AxisName(InAxisName)
	{ }
};

/** Binds a delegate to an action. */
struct FInputActionBinding : public FInputBinding
{
private:
	/** Friendly name of action, e.g "jump" */
	FString ActionName;

public:
	/** Key event to bind it to, e.g. pressed, released, double click */
	EInputEvent KeyEvent = EInputEvent::IE_Pressed;

	/** The delegate bound to the action */
	TFunction<void(void)> ActionDelegate;

	FInputActionBinding(const FString& InActionName, const EInputEvent InKeyEvent)
		: FInputBinding()
		, KeyEvent(InKeyEvent)
		, ActionName(InActionName)
	{ }

	const FStringView GetActionName() const { return ActionName; }
};

class AInputManager
{
public:
	AInputManager();
	virtual ~AInputManager() = default;

	virtual void KeyboardEvent(const struct FKeyboardEvent& Event);
	virtual void MouseButtonEvent(const struct FMouseButtonEvent& Event);
	virtual void MouseMotionEvent(const struct FMouseMotionEvent& Event);

	virtual void BindAxis(const FString& AxisName, TFunction<void(float)> Function);
	virtual void BindAction(const FString& ActionName, EInputEvent KeyEvent, TFunction<void(void)> Function);

private:
	/** The collection of axis bindings. */
	TArray<FInputAxisBinding> AxisBindings;

	/** The collection of action bindings. */
	TArray<FInputActionBinding> ActionBindings;
};
