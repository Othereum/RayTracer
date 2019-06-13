#include "../Public/Dielectric.h"
#include "../Public/Color.h"
#include "../Public/Hitable.h"
#include "../Public/Math.h"
#include "../Public/Ray.h"

bool MDielectric::Scatter(const FRay& Ray, const FHitRecord& Record,
	FLinearColor& OutAttenuation, FRay& OutScattered) const
{
	OutAttenuation = { 1.f, 1.f, 1.f };
	FVector OutwardNormal;
	float NiOverNt;
	float Cosine;
	if (const float D = FVector::Dot(Ray.Dir, Record.Normal); D > 0.f)
	{
		OutwardNormal = -Record.Normal;
		NiOverNt = RefractiveIndex;
		Cosine = RefractiveIndex * D / Ray.Dir.Size();
	}
	else
	{
		OutwardNormal = Record.Normal;
		NiOverNt = 1.f / RefractiveIndex;
		Cosine = -D / Ray.Dir.Size();
	}
	
	float ReflectProb;
	FVector Refracted;
	if (Math::Refract(Ray.Dir, OutwardNormal, NiOverNt, Refracted))
	{
		ReflectProb = Math::Schlick(Cosine, RefractiveIndex);
	}
	else
	{
		ReflectProb = 1.f;
	}
	OutScattered = { Record.HitLocation, Math::Rand() < ReflectProb ? Math::Reflect(Ray.Dir, Record.Normal) : Refracted };

	return true;
}
