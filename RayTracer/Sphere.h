// Copyright (c) 2019, Othereum. All rights reserved.
#pragma once
#include "Hitable.h"

class Sphere : public Hitable
{
public:
	Sphere() {}
	Sphere(const FVector& Center, float Radius) :Center{ Center }, Radius{ Radius } {}
	
	virtual bool Hit(HitRecord& OutRecord, const FRay& Ray,
		float TMin = 0, float TMax = std::numeric_limits<float>::max()) const override;

	FVector Center;
	float Radius = 0;
};
