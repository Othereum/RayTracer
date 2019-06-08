// Copyright (c) 2019, Othereum. All rights reserved.
#pragma once
#include "Vector.h"

struct Ray
{
	FVector Origin, Dir;

	Ray() {}
	Ray(const FVector& Origin, const FVector& Dir) :Origin{ Origin }, Dir{ Dir } {}
	
	FVector PointAtParam(float T) const { return Origin + T * Dir; }
};
