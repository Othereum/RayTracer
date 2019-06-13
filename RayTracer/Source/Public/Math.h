#pragma once

struct FVector;
namespace Math
{
	template <class T>
	T Lerp(const T& A, const T& B, float t)
	{
		return (1.f - t) * A + t * B;
	}

	float Rand(float Min = 0, float Max = 1);
	FVector RandomInUnitSphere();
	FVector RandomInUnitCircle();
	FVector Reflect(const FVector& V, const FVector& N);
	bool Refract(const FVector& V, const FVector& N, float NiOverNt, FVector& OutRefracted);
	float Schlick(float Cosine, float RefractiveIndex);
}
