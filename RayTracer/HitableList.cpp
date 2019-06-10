// Copyright (c) 2019, Othereum. All rights reserved.
#include "HitableList.h"
#include "Ray.h"

bool HitableList::Hit(HitRecord& OutRecord, const FRay& Ray, float TMin, float TMax) const
{
	HitRecord TmpRecord;
	bool bHit = false;
	float ClosestSoFar = TMax;
	for (const std::unique_ptr<Hitable>& Hitable : List)
	{
		if (Hitable->Hit(TmpRecord, Ray, TMin, ClosestSoFar))
		{
			bHit = true;
			ClosestSoFar = TmpRecord.T;
			OutRecord = TmpRecord;
		}
	}
	return bHit;
}
