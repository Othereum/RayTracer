#include "../Public/Metal.h"
#include <algorithm>
#include "../Public/Hitable.h"
#include "../Public/Math.h"
#include "../Public/Ray.h"

MMetal::MMetal(const FLinearColor& Albedo, float Fuzziness)
	:Albedo{ Albedo }, Fuzziness{ std::min(Fuzziness, 1.f) }
{
}

bool MMetal::Scatter(const FRay& Ray, const FHitRecord& Record,
	FLinearColor& OutAttenuation, FRay& OutScattered) const
{
	FVector Reflected = Math::Reflect(FVector::GetNormal(Ray.Dir), Record.Normal);
	OutScattered = { Record.HitLocation, Reflected + Fuzziness * Math::RandomInUnitSphere() };
	OutAttenuation = Albedo;
	return FVector::Dot(OutScattered.Dir, Record.Normal) > 0.f;
}
