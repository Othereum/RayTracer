#pragma once
#include <string>
#include <ostream>

struct FConfig
{
	FConfig();

	std::string ImageFileName;
	unsigned Width;
	unsigned Height;
	unsigned NumAASamples;

	unsigned NumThread;

	float Ratio;
	unsigned NumPixel;
};

static std::ostream& operator<<(std::ostream& os, const FConfig& Config)
{
	os << "Resolution: " << Config.Width << 'x' << Config.Height << '\n'
		<< "AA samples: " << Config.NumAASamples;
	return os;
}

static const FConfig& GetConfig()
{
	const static FConfig Config;
	return Config;
}
