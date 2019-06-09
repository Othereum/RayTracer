// Copyright (c) 2019, Othereum. All rights reserved.

#include <chrono>
#include <fstream>
#include <iostream>

#include "Color.h"
#include "Math.h"
#include "Ray.h"

constexpr auto FileName = "image.ppm";
constexpr unsigned Width = 200;
constexpr unsigned Height = 100;

bool HitSphere(const FVector& Center, float Radius, const FRay& Ray)
{
	const FVector oc = Ray.Origin - Center;
	const float a = Ray.Dir.SqrSize();
	const float b = 2 * FVector::Dot(oc, Ray.Dir);
	const float c = oc.SqrSize() - Radius * Radius;
	const float d = b*b - 4*a*c;
	return d > 0;
}

FColor Color(const FRay& Ray)
{
	if (HitSphere({ 1, 0, 0 }, .5, Ray))
	{
		return FColor::Red;
	}

	const FVector NormalDir = FVector::GetNormal(Ray.Dir);
	const float t = .5f * (NormalDir.Z + 1);
	return Math::Lerp(FLinearColor::White, { .5f, .7f, 1 }, t);
}

void Draw(std::ostream& Output)
{
	const FVector LowerLeftCorner{ 1, -2, -1 };
	const FVector Horizontal{ 0, 4, 0 };
	const FVector Vertical{ 0, 0, 2 };
	const FVector Origin;
	for (unsigned y = 0; y < Height; ++y)
	{
		for (unsigned x = 0; x < Width; ++x)
		{
			const float u = static_cast<float>(x) / Width;
			const float v = (Height - y - 1.f) / Height;
			const FRay Ray{ Origin, LowerLeftCorner + u * Horizontal + v * Vertical };
			Output << Color(Ray) << '\n';
		}
	}
}

void CreateImageFile()
{
	std::ofstream OutImageFile{ FileName };
	OutImageFile << "P3\n" << Width << ' ' << Height << "\n255\n";
	Draw(OutImageFile);
}

int main()
{
	using namespace std::chrono;
	const auto Start = system_clock::now();
	CreateImageFile();
	std::cout << FileName << " created successfully!\nTime took: " << duration<float>{system_clock::now() - Start}.count() << "s\n";
}
