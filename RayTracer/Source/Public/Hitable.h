// Copyright (c) 2019, Othereum. All rights reserved.
#pragma once
#include <limits>
#include "Vector.h"

struct FHitRecord
{
	float T;
	FVector HitLocation;
	FVector Normal;
};

struct FRay;

class FHitable
{
public:
	virtual bool Hit(FHitRecord& OutRecord, const FRay& Ray,
		float TMin = .001f, float TMax = std::numeric_limits<float>::max()) const = 0;
};
