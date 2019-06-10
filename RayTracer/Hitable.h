// Copyright (c) 2019, Othereum. All rights reserved.
#pragma once
#include <limits>
#include "Vector.h"

struct HitRecord
{
	float T;
	FVector HitLocation;
	FVector Normal;
};

struct FRay;

class Hitable
{
public:
	virtual bool Hit(HitRecord& OutRecord, const FRay& Ray,
		float TMin = 0, float TMax = std::numeric_limits<float>::max()) const = 0;
};
