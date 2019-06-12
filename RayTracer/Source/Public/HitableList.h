#pragma once
#include <memory>
#include <vector>
#include "Hitable.h"

class HHitableList : public HHitable
{
public:
	HHitableList() {}
	HHitableList(std::vector<std::unique_ptr<HHitable>>&& List) :List{ std::move(List) } {}

	virtual bool Hit(FHitRecord& OutRecord, const FRay& Ray, float TMin, float TMax) const override;

	std::vector<std::unique_ptr<HHitable>> List;
};
