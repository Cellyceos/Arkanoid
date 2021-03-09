//
//  AScreensManager.h
//  Screen Manager based on FSM.
//
//  Created by Kirill Bravichev on 03/05/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IScreensCreator.h"
#include "Interfaces/IMessageHendler.h"

class AScreensManager : public IMessageHandler, public std::enable_shared_from_this<AScreensManager>
{
public:
    AScreensManager(const TSharedPtr<IScreensCreator>& ScreensCreator);
	virtual ~AScreensManager();

    void Update(float DeltaTime);
    void Draw(const TSharedPtr<ARendererClass>& Renderer) const;

    virtual void SetBackgroundColor(const FColor& Color) { BackgroundColor = Color; }
    virtual FColor GetBackgroundColor() const { return BackgroundColor; }

    virtual void RequestScreenTransition(int32 ScreenId) { RequestScreenId = ScreenId; }
    virtual void RequestToQuit();

protected:
    virtual void TransitState();

    /// Begin IMessageHandler
    virtual void OnKeyDown(const struct SDL_KeyboardEvent& Event) override;
    virtual void OnKeyUp(const struct SDL_KeyboardEvent& Event)  override;
    virtual void OnMouseButtonDown(const struct SDL_MouseButtonEvent& Event) override;
    virtual void OnMouseButtonUp(const struct SDL_MouseButtonEvent& Event) override;
    virtual void OnMouseMotion(const struct SDL_MouseMotionEvent& Event)  override;

    virtual void OnWindowsFocusGained() override;
    virtual void OnWindowsFocusLost() override;
    /// End IMessageHandler

private:
    const TSharedPtr<IScreensCreator> ScreensCreator;
    
    FColor BackgroundColor{ 30, 30, 30, 255 };
    int32 RequestScreenId{ IScreensCreator::InvalidRequestId };

    TArray<TSharedPtr<AScreenState>> ActiveScreens;
};
