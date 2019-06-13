#pragma once
#include "Material.h"

class MDielectric : public MMaterial
{
public:
	MDielectric(float RefractiveIndex) :RefractiveIndex{ RefractiveIndex } {}

	virtual bool Scatter(const struct FRay& Ray, const struct FHitRecord& Record,
		struct FLinearColor& OutAttenuation, FRay& OutScattered) const override;

	float RefractiveIndex;
};