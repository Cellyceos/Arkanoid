#pragma once

#include "AObject.h"
class AGameUI : public AObject
{
public:
	virtual void Update(float DeltaTime) override;
	virtual void Draw(const TSharedPtr<class SDLRenderer>& Renderer) const override;
};

