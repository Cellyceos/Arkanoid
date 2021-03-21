//
//  AScreensManager.h
//  Screen Manager based on FSM.
//
//  Created by Kirill Bravichev on 03/05/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "BasicTypes.h"
#include "Interfaces/IScreensCreator.h"
#include "Interfaces/IScreenRequestSolver.h"
#include "Interfaces/IMessageHendler.h"


class AScreensManager : public IMessageHandler, public std::enable_shared_from_this<AScreensManager>
{
public:
    AScreensManager(TUniquePtr<IScreensCreator>&& InScreensCreator, TUniquePtr<IScreenRequestSolver>&& InScreenRequestSolver = nullptr);
	virtual ~AScreensManager();

    void Update(float DeltaTime);
    void Draw(const TSharedPtr<ARendererClass>& Renderer) const;

    virtual void SetBackgroundColor(const FColor& Color) { BackgroundColor = Color; }
    virtual FColor GetBackgroundColor() const { return BackgroundColor; }

    virtual void RequestScreenTransition(const TSharedPtr<AScreenState>& Requester, int32 ScreenId, int32 Reason);
    virtual void RequestToQuit();

protected:
    virtual void TransitState();

    /// Begin IMessageHandler
    virtual void OnKeyDown(const FKeyboardEvent& Event) override;
    virtual void OnKeyUp(const FKeyboardEvent& Event)  override;
    virtual void OnMouseButtonDown(const FMouseButtonEvent& Event) override;
    virtual void OnMouseButtonUp(const FMouseButtonEvent& Event) override;
    virtual void OnMouseMotion(const FMouseMotionEvent& Event)  override;

    virtual void OnWindowsFocusGained() override;
    virtual void OnWindowsFocusLost() override;
    /// End IMessageHandler

private:
    const TUniquePtr<const IScreensCreator> ScreensCreator;
    const TUniquePtr<const IScreenRequestSolver> ScreenRequestSolver;
    
    FColor BackgroundColor{ 30, 30, 30, 255 };
    int32 RequestScreenId{ IScreensCreator::InvalidScreenId };

    TArray<TSharedPtr<AScreenState>> ActiveScreens;
};
