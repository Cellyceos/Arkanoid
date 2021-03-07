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

	virtual void Update(float DeltaTime) override;
	virtual void Draw(const TSharedPtr<class SDLRenderer>& Renderer) const override;

private:
	FPoint Direction;
};
