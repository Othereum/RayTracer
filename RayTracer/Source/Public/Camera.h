#pragma once
#include "Vector.h"

class FCamera
{
public:
	FCamera() {}
	FCamera(const FVector& Origin, const FVector& LowerLeftCorner, const FVector& Horizontal, const FVector& Vertical)
		:Origin{ Origin }, LowerLeftCorner{ LowerLeftCorner }, Horizontal{ Horizontal }, Vertical{ Vertical }
	{
	}

	struct FRay GetRay(float U, float V) const;
	
	FVector Origin;
	FVector LowerLeftCorner;
	FVector Horizontal;
	FVector Vertical;
};
