//
//  ABall.h
//  Ball object class.
//
//  Created by Kirill Bravichev on 03/02/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "AObject.h"


class ABall : public AObject
{
public:
	ABall();
	virtual ~ABall();

	virtual void Update(float DeltaTime) override;
	virtual void Draw(const TSharedPtr<class SDLRenderer>& Renderer) const override;

	virtual void OnCollisionEnter(const TSharedPtr<AObject>& Col) override;
	virtual bool ShouldBeDestroyed() const  override { return bShouldBeDestroed; }

	virtual void AttachTo(const TWeakPtr<AObject>& Parent)  override;

private:
	bool bShouldBeDestroed{ false };
	FPoint Direction{0.0f, 1.0f};

	const float Speed{ 600.0f };
	const FColor BackGroundColor{ 100, 100, 100, 255 };
	const FColor MiddleColor{ 125, 125, 125, 255 };
	const FColor ForegroundColor{ 150, 150, 150, 255 };
};
