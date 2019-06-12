#include "../Public/Metal.h"
#include "../Public/Hitable.h"
#include "../Public/Math.h"
#include "../Public/Ray.h"

bool MMetal::Scatter(const FRay& Ray, const FHitRecord& Record,
	FLinearColor& OutAttenuation, FRay& OutScattered) const
{
	FVector Reflected = Math::Reflect(FVector::GetNormal(Ray.Dir), Record.Normal);
	OutScattered = { Record.HitLocation, Reflected };
	OutAttenuation = Albedo;
	return FVector::Dot(OutScattered.Dir, Record.Normal) > 0.f;
}
