// Copyright (c) 2019, Othereum. All rights reserved.
#pragma once
#include <memory>
#include <vector>
#include "Hitable.h"

class HitableList : public Hitable
{
public:
	HitableList() {}
	HitableList(std::vector<std::unique_ptr<Hitable>>&& List) :List{ std::move(List) } {}

	virtual bool Hit(HitRecord& OutRecord, const FRay& Ray,
		float TMin = 0, float TMax = std::numeric_limits<float>::max()) const override;

	std::vector<std::unique_ptr<Hitable>> List;
};
