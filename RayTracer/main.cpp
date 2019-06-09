// Copyright (c) 2019, Othereum. All rights reserved.

#include <chrono>
#include <fstream>
#include <iostream>

#include "Color.h"
#include "Math.h"
#include "Ray.h"

constexpr auto FileName = "image.ppm";
constexpr unsigned Width = 960;
constexpr unsigned Height = 540;
constexpr float Ratio = Width * 1.f / Height;
const FVector SphereLocation{ 1, 0, 0 };
constexpr float SphereRadius = .5;

float HitSphere(const FVector& Center, float Radius, const FRay& Ray)
{
	const FVector oc = Ray.Origin - Center;
	const float a = Ray.Dir.SqrSize();
	const float b = 2 * FVector::Dot(oc, Ray.Dir);
	const float c = oc.SqrSize() - Radius * Radius;
	const float d = b*b - 4*a*c;
	return d < 0 ? -1 : (-b - sqrt(d)) / (2 * a);
}

FColor Color(const FRay& Ray)
{
	if (const float T = HitSphere(SphereLocation, SphereRadius, Ray);
		T > 0)
	{
		const FVector N = FVector::GetNormal(Ray.PointAtParam(T) - SphereLocation);
		return .5 * (FLinearColor{ N.X, N.Y, N.Z } + FLinearColor::White);
	}

	const FVector NormalDir = FVector::GetNormal(Ray.Dir);
	const float t = .5f * (NormalDir.Z + 1);
	return Math::Lerp(FLinearColor::White, { .5f, .7f, 1 }, t);
}

void Draw(std::ostream& Output)
{
	const FVector Horizontal{ 0, 4, 0 };
	const FVector Vertical{ 0, 0, Horizontal.Y / Ratio };
	const FVector LowerLeftCorner{ 1, Horizontal.Y * -.5f, Vertical.Z * -.5f };
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
