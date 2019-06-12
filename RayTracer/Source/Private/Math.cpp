#include "../Public/Math.h"
#include <random>
#include "../Public/Vector.h"

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

FVector Math::Reflect(const FVector& V, const FVector& N)
{
	return V - 2.f * FVector::Dot(V, N) * N;
}

float Math::Rand(float Min, float Max)
{
	static std::default_random_engine re{ std::random_device{}() };
	return std::uniform_real_distribution{ Min, Max }(re);
}
