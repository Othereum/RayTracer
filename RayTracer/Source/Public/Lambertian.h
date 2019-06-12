#pragma once
#include "Material.h"
#include "Color.h"

class MLambertian : public MMaterial
{
public:
	MLambertian(const FLinearColor& Albedo) :Albedo{ Albedo } {}

	virtual bool Scatter(const FRay& Ray, const FHitRecord& Record,
		FLinearColor& OutAttenuation, FRay& OutScattered) const override;

	FLinearColor Albedo;
};