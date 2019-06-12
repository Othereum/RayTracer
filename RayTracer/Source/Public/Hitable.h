#pragma once
#include <limits>
#include <memory>
#include "Material.h"
#include "Vector.h"

struct FHitRecord
{
	float T;
	FVector HitLocation;
	FVector Normal;
	std::shared_ptr<MMaterial> Material;
};

class HHitable
{
public:
	virtual bool Hit(FHitRecord& OutRecord, const struct FRay& Ray,
		float TMin = .001f, float TMax = std::numeric_limits<float>::max()) const = 0;
};
