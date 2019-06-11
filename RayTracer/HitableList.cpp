// Copyright (c) 2019, Othereum. All rights reserved.
#include "HitableList.h"
#include "Ray.h"

bool FHitableList::Hit(FHitRecord& OutRecord, const FRay& Ray, float TMin, float TMax) const
{
	FHitRecord TmpRecord;
	bool bHit = false;
	float ClosestSoFar = TMax;
	for (const std::unique_ptr<FHitable>& FHitable : List)
	{
		if (FHitable->Hit(TmpRecord, Ray, TMin, ClosestSoFar))
		{
			bHit = true;
			ClosestSoFar = TmpRecord.T;
			OutRecord = TmpRecord;
		}
	}
	return bHit;
}
