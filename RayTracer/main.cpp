// Copyright (c) 2019, Othereum. All rights reserved.

#include <fstream>
#include "Color.h"

int main()
{
	std::ofstream OutImageFile{ "image.ppm" };
	static constexpr unsigned Width = 1920;
	static constexpr unsigned Height = 1080;
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
