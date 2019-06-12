#pragma once

struct FVector;
namespace Math
{
	template <class T>
	T Lerp(const T& A, const T& B, float t)
	{
		return (1.f - t) * A + t * B;
	}

	FVector RandomInUnitSphere();
	FVector Reflect(const FVector& V, const FVector& N);
	float Rand(float Min = 0, float Max = 1);
}
