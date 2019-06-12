// Copyright (c) 2019, Othereum. All rights reserved.
#include "../Public/Ray.h"
#include "../Public/Sphere.h"

bool FSphere::Hit(FHitRecord& OutRecord, const FRay& Ray, float TMin, float TMax) const
{
	const FVector oc = Ray.Origin - Center;
	const float a = Ray.Dir.SqrSize();
	const float b = FVector::Dot(oc, Ray.Dir);
	const float c = oc.SqrSize() - Radius * Radius;
	const float d = b * b - a * c;

	if (d > 0)
	{
		auto f = [&](float T)
		{
			if (TMin < T && T < TMax)
			{
				OutRecord.T = T;
				OutRecord.HitLocation = Ray.PointAtParam(T);
				OutRecord.Normal = (OutRecord.HitLocation - Center) / Radius;
				return true;
			}
			return false;
		};
		const float SqrtD = sqrt(d);
		return f((-b - SqrtD) / a) || f((-b + SqrtD) / a);
	}

	return false;
}
