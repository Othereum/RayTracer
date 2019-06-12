#include "../Public/HitableList.h"
#include "../Public/Ray.h"

bool HHitableList::Hit(FHitRecord& OutRecord, const FRay& Ray, float TMin, float TMax) const
{
	bool bHit = false;
	float ClosestSoFar = TMax;
	for (const std::unique_ptr<HHitable>& HHitable : List)
	{
		if (HHitable->Hit(OutRecord, Ray, TMin, ClosestSoFar))
		{
			bHit = true;
			ClosestSoFar = OutRecord.T;
		}
	}
	return bHit;
}
