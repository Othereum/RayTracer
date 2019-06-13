#pragma once
class MMaterial
{
public:
	virtual bool Scatter(const struct FRay& Ray, const struct FHitRecord& Record,
		struct FLinearColor& OutAttenuation, FRay& OutScattered) const = 0;

	virtual float GetReflector() const { return 1.f; }
};
