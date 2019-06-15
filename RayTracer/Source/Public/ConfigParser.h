#pragma once
#include <string>
#include <unordered_map>

struct FConfig
{
	FConfig(const char* ConfigFileName);

	std::string ImageFileName;
	unsigned Width;
	unsigned Height;
	unsigned NumAASamples;
	unsigned NumThread = std::thread::hardware_concurrency() * 5 / 2;
};

const FConfig& GetConfig()
{
	const static FConfig Config;
	return Config;
}
