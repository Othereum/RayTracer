// Copyright (c) 2019, Othereum. All rights reserved.
#pragma once
#include "Hitable.h"

class FSphere : public FHitable
{
public:
	FSphere() {}
	FSphere(const FVector& Center, float Radius) :Center{ Center }, Radius{ Radius } {}
	
	virtual bool Hit(FHitRecord& OutRecord, const FRay& Ray,
		float TMin = std::numeric_limits<float>::min(),
		float TMax = std::numeric_limits<float>::max()) const override;

	FVector Center;
	float Radius = 0;
};
