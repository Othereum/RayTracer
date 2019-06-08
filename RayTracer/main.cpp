// Copyright (c) 2019, Othereum. All rights reserved.
#include <chrono>
#include <fstream>
#include <iostream>
#include "Color.h"

constexpr auto FileName = "image.ppm";
constexpr unsigned Width = 200;
constexpr unsigned Height = 100;

void CreateImageFile()
{
	std::ofstream OutImageFile{ FileName };
	OutImageFile << "P3\n" << Width << ' ' << Height << "\n255\n";
	for (unsigned Y = 0; Y < Height; ++Y)
	{
		for (unsigned X = 0; X < Width; ++X)
		{
			const float R = static_cast<float>(X) / Width;
			const float G = static_cast<float>(Height - Y - 1) / Height;
			const float B = .2f;
			OutImageFile << FColor{ FLinearColor{R, G, B} } << '\n';
		}
	}
}

int main()
{
	using namespace std::chrono;
	const auto Start = system_clock::now();
	CreateImageFile();
	std::cout << FileName << " created successfully!\nTime took: " << duration<float>{system_clock::now() - Start}.count() << "s\n";
}
