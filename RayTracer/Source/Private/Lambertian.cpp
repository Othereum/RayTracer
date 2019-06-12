#include "../Public/Lambertian.h"
#include "../Public/Hitable.h"
#include "../Public/Math.h"
#include "../Public/Ray.h"

bool MLambertian::Scatter(const FRay& Ray, const FHitRecord& Record,
	FLinearColor& OutAttenuation, FRay& OutScattered) const
{
	FVector Target = Record.HitLocation + Math::RandomInUnitSphere();
	OutScattered = { Record.HitLocation, Target - Record.HitLocation };
	OutAttenuation = Albedo;
	return true;
}
