#pragma once
#include <memory>
#include "Hitable.h"

class HSphere : public HHitable
{
public:
	HSphere() {}
	HSphere(const FVector& Center, float Radius, std::shared_ptr<MMaterial>&& Material)
		:Center{ Center }, Radius{ Radius }, Material{ std::move(Material) } {}
	
	virtual bool Hit(FHitRecord& OutRecord, const FRay& Ray, float TMin, float TMax) const override;

	FVector Center;
	float Radius = 0;
	std::shared_ptr<MMaterial> Material;
};
