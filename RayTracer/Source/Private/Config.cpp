#include "../Public/Config.h"
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>

using namespace std::string_literals;
const auto ConfigFileName = "config.ini"s;
const auto kImageFileName = "OutputImageFileName"s;
const auto kWidth = "Width"s;
const auto kHeight = "Height"s;
const auto kNumAASamples = "NumOfAASamples"s;
const auto kNumThread = "OverrideNumOfThreads"s;

void UnableToReadConfig()
{
	if (!std::ifstream{ ConfigFileName })
	{
		std::ofstream os{ ConfigFileName };
		os << kImageFileName << "=image.ppm #You can use \"double quotes\" to enter spaces\n"
			<< kWidth << "=960\n"
			<< kHeight << "=540\n"
			<< kNumAASamples << "=10\n"
			<< kNumThread << "=0 ;0 to use auto detect";
	}
	std::cout << "Please write " << ConfigFileName << '\n';
	throw std::exception{ "Unable to read configuration file" };
}

auto ParseConfig()
{
	std::ifstream is{ ConfigFileName };
	if (!is) UnableToReadConfig();
	std::unordered_map<std::string, std::string> Parsed;
	std::string LineBuf;
	while (std::getline(is, LineBuf))
	{
		std::string Key, Value;
		bool bEnterKey = true;
		bool bEnterStr = false;
		for (char c : LineBuf)
		{
			if (isspace(c) && !bEnterStr) continue;
			if (c == ';' || c == '#') break;
			if (c == '=') bEnterKey = false;
			else if (!bEnterKey && c == '"') bEnterStr = true;
			else (bEnterKey ? Key : Value) += c;
		}
		if (Key.empty() || Value.empty()) UnableToReadConfig();
		Parsed[std::move(Key)] = std::move(Value);
	}
	return Parsed;
}

FConfig::FConfig()
{
	auto Parsed = ParseConfig();

	ImageFileName = std::move(Parsed[kImageFileName]);
	Width = std::stoul(Parsed[kWidth]);
	Height = std::stoul(Parsed[kHeight]);
	NumAASamples = std::stoul(Parsed[kNumAASamples]);

	NumThread = std::stoul(Parsed[kNumThread]);
	if (NumThread == 0) NumThread = std::thread::hardware_concurrency() * 5 / 2;

	Ratio = static_cast<float>(Width) / Height;
	NumPixel = Width * Height;
}
