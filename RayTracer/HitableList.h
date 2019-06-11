// Copyright (c) 2019, Othereum. All rights reserved.
#pragma once
#include <memory>
#include <vector>
#include "Hitable.h"

class FHitableList : public FHitable
{
public:
	FHitableList() {}
	FHitableList(std::vector<std::unique_ptr<FHitable>>&& List) :List{ std::move(List) } {}

	virtual bool Hit(FHitRecord& OutRecord, const FRay& Ray,
		float TMin = std::numeric_limits<float>::min(),
		float TMax = std::numeric_limits<float>::max()) const override;

	std::vector<std::unique_ptr<FHitable>> List;
};
