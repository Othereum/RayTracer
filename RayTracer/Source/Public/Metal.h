#pragma once
#include "Material.h"
#include "Color.h"

class MMetal : public MMaterial
{
public:
	MMetal(const FLinearColor& Albedo, float Fuzziness);

	virtual bool Scatter(const FRay& Ray, const FHitRecord& Record,
		FLinearColor& OutAttenuation, FRay& OutScattered) const override;

	FLinearColor Albedo;
	float Fuzziness;
};