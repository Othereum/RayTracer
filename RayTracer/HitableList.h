// Copyright (c) 2019, Othereum. All rights reserved.
#pragma once
#include <memory>
#include <vector>
#include "Hitable.h"

class HitableList : public Hitable
{
	std::vector<std::unique_ptr<Hitable>> List;

public:
	HitableList() {}
	HitableList(decltype(List)&& List) :List{ std::move(List) } {}

	virtual bool Hit(HitRecord& OutRecord, const FRay& Ray,
		float TMin = 0, float TMax = std::numeric_limits<float>::max()) const override;
};
