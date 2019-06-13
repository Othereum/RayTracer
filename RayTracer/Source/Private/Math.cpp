#include "../Public/Math.h"
#include <random>
#include "../Public/Vector.h"

float Math::Rand(float Min, float Max)
{
	static std::default_random_engine re{ std::random_device{}() };
	return std::uniform_real_distribution{ Min, Max }(re);
}

FVector Math::RandomInUnitSphere()
{
	while (true)
	{
		if (FVector P{ Rand(-1), Rand(-1), Rand(-1) };
			P.SqrSize() >= 1.f)
		{
			return P;
		}
	}
}

FVector Math::RandomInUnitCircle()
{
	while (true)
	{
		if (FVector P{ Rand(-1), Rand(-1), 0 };
			P.SqrSize() >= 1.f)
		{
			return P;
		}
	}
}

FVector Math::Reflect(const FVector& V, const FVector& N)
{
	return V - 2.f * FVector::Dot(V, N) * N;
}

bool Math::Refract(const FVector& V, const FVector& N, float NiOverNt, FVector& OutRefracted)
{
	FVector NV = FVector::GetNormal(V);
	float DT = FVector::Dot(NV, N);
	float D = 1.f - NiOverNt * NiOverNt * (1.f - DT * DT);
	if (D > 0)
	{
		OutRefracted = NiOverNt * (NV - N * DT) - N * sqrt(D);
		return true;
	}
	return false;
}

float Math::Schlick(float Cosine, float RefractiveIndex)
{
	float R0 = (1.f - RefractiveIndex) / (1.f + RefractiveIndex);
	R0 *= R0;
	return R0 + (1.f - R0) * pow(1.f - Cosine, 5);
}
