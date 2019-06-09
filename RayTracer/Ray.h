// Copyright (c) 2019, Othereum. All rights reserved.
#pragma once
#include "Vector.h"

struct FRay
{
	// Origin location
	FVector Origin;
	
	// Ray direction
	// Note that it may not be a unit vector
	FVector Dir;

	FRay() {}
	FRay(const FVector& Origin, const FVector& Dir) :Origin{ Origin }, Dir{ Dir } {}
	
	FVector PointAtParam(float T) const { return Origin + T * Dir; }
};
