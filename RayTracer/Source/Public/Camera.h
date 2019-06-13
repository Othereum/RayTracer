#pragma once
#include "Vector.h"

class FCamera
{
public:
	FCamera(FVector LookFrom, FVector LookAt, FVector vUp, float vFov, float Aspect, float Aperture, float FocusDist)
		:Origin{ LookFrom },
		W{ FVector::GetNormal(LookFrom - LookAt) },
		U{ FVector::GetNormal(FVector::Cross(vUp, W)) },
		V{ FVector::Cross(W, U) },
		LensRadius{ Aperture / 2.f }
	{
		const float Theta = vFov * 3.14159265f / 180.f;
		const float HalfHeight = tan(Theta / 2);
		const float HalfWidth = Aspect * HalfHeight;
		LowerLeftCorner = Origin - HalfWidth * FocusDist * U - HalfHeight * FocusDist * V - FocusDist * W;
		Horizontal = 2.f * HalfWidth * FocusDist * U;
		Vertical = 2.f * HalfHeight * FocusDist * V;
	}

	struct FRay GetRay(float U, float V) const;
	
	FVector Origin;
	FVector LowerLeftCorner;
	FVector Horizontal;
	FVector Vertical;
	FVector W, U, V;
	float LensRadius;
};
