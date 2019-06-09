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
			const float v = static_cast<float>(Height - y - 1) / Height;
			const FRay r{ Origin, LowerLeftCorner + u * Horizontal + v * Vertical };
			const float t = .5f * (FVector::GetNormal(r.Dir).Z + 1.f);
			const FColor Color = Math::Lerp<FLinearColor>({}, { .5f, .7f, 1.f }, t);
			Output << Color << '\n';
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
