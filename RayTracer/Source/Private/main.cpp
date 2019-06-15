#include <chrono>
#include <fstream>
#include <future>
#include <iostream>
#include <vector>

#include "../Public/Camera.h"
#include "../Public/Color.h"
#include "../Public/Config.h"
#include "../Public/Dielectric.h"
#include "../Public/HitableList.h"
#include "../Public/Lambertian.h"
#include "../Public/Math.h"
#include "../Public/Metal.h"
#include "../Public/Ray.h"
#include "../Public/Sphere.h"

using namespace std::chrono;

FLinearColor GetColor(const FRay& Ray, const HHitable& World, unsigned Depth = 0)
{
	if (FHitRecord Record; World.Hit(Record, Ray))
	{
		FRay Scattered;
		FLinearColor Attenuation;
		if (Depth < 50 && Record.Material->Scatter(Ray, Record, Attenuation, Scattered))
		{
			return Attenuation * GetColor(Scattered, World, Depth + 1);
		}
		return FLinearColor::Black;
	}

	const FVector NormalDir = FVector::GetNormal(Ray.Dir);
	const float t = .5f * (NormalDir.Z + 1.f);
	return Math::Lerp(FLinearColor::White, { .5f, .7f, 1.f }, t);
}

std::string FormatDuration(unsigned Seconds, bool bShort = false)
{
	std::string Result;
	if (Seconds >= 3600)
	{
		Result += std::to_string(Seconds / 3600);
		Result += "h ";
		if (bShort) return Result;
		Seconds %= 3600;
	}
	if (Seconds >= 60)
	{
		Result += std::to_string(Seconds / 60);
		Result += "m ";
		if (bShort) return Result;
		Seconds %= 60;
	}
	if (Seconds > 0 || Result.size() == 0)
	{
		Result += std::to_string(Seconds);
		Result += 's';
	}
	return Result;
}

void Draw(std::vector<std::vector<FColor>>& Output, const time_point<system_clock>& Start)
{
	FVector LookFrom{ -3, 13, 2 };
	FVector LookAt{ 0, 0, 0 };
	float DistToFocus = 10;
	float Aperture = .1f;
	FCamera Camera{ LookFrom, LookAt, {0.f, 0.f, 1.f}, 20, GetConfig().Ratio, Aperture, DistToFocus };

	HHitableList World;
	World.List.push_back(std::make_unique<HSphere>(FVector{ 0, 0, -1000 }, 1000.f, std::make_unique<MLambertian>(FLinearColor{ .5f, .5f, .5f })));
	for (int a = -11; a < 11; ++a)
	{
		for (int b = -11; b < 11; ++b)
		{
			float ChooseMat = Math::Rand();
			FVector Center{ a + Math::Rand(0, .9f), b + Math::Rand(0, .9f), .2f };
			if ((Center - FVector{ 4, .2f, 0 }).Size() > .9f)
			{
				if (ChooseMat < .8f)
				{
					World.List.push_back(std::make_unique<HSphere>(Center, .2f, std::make_unique<MLambertian>(FLinearColor{ Math::Rand() * Math::Rand(), Math::Rand() * Math::Rand() , Math::Rand() * Math::Rand() })));
				}
				else if (ChooseMat < .95f)
				{
					World.List.push_back(std::make_unique<HSphere>(Center, .2f, std::make_unique<MMetal>(FLinearColor{ Math::Rand(.5), Math::Rand(.5), Math::Rand(.5) }, Math::Rand(0, .5))));
				}
				else
				{
					World.List.push_back(std::make_unique<HSphere>(Center, .2f, std::make_unique<MDielectric>(1.5f)));
				}
			}
		}
	}
	World.List.push_back(std::make_unique<HSphere>(FVector{ 0, 0, 1 }, 1.f, std::make_unique<MDielectric>(1.5f)));
	World.List.push_back(std::make_unique<HSphere>(FVector{ 0, -4, 1 }, 1.f, std::make_unique<MLambertian>(FLinearColor{ .4f, .2f, .1f })));
	World.List.push_back(std::make_unique<HSphere>(FVector{ 0, 4, 1 }, 1.f, std::make_unique<MMetal>(FLinearColor{ .7f, .6f, .5f }, 0.f)));

	std::atomic<unsigned> pp = 0;
	auto Draw = [&](unsigned YS, unsigned YE)
	{
		for (unsigned y = YS; y < YE; ++y)
		{
			const float v = (GetConfig().Height - y - 1.f) / GetConfig().Height;
			for (unsigned x = 0; x < GetConfig().Width; ++x)
			{
				const float u = (x * 1.f) / GetConfig().Width;
				FLinearColor Color = GetColor(Camera.GetRay(u, v), World);
				for (unsigned s = 0; s < GetConfig().NumAASamples; ++s)
				{
					Color += GetColor(Camera.GetRay(u + Math::Rand() / GetConfig().Width, v + Math::Rand() / GetConfig().Height), World);
				}
				Color /= GetConfig().NumAASamples + 1.f;
				Output[y][x] = Color;
				++pp;
			}
		}
	};

	std::vector<std::future<void>> fv;
	fv.reserve(GetConfig().NumThread);
	const unsigned ntr = GetConfig().Height / GetConfig().NumThread;
	for (unsigned i = 0; i < GetConfig().NumThread - 1; ++i)
		fv.push_back(std::async(Draw, ntr * i, ntr * (i + 1)));
	fv.push_back(std::async(Draw, ntr * (GetConfig().NumThread-1), GetConfig().Height));
	std::cout << "Created " << GetConfig().NumThread << " parallel tasks.\n\n";
	
	float OldP = 0.f;
	auto Last = system_clock::now();
	float Remaining = 0.f;
	while (pp < GetConfig().NumPixel)
	{
		const float NewP = 100.f * pp / GetConfig().NumPixel;
		auto Now = system_clock::now();
		if (static_cast<unsigned>(NewP) > static_cast<unsigned>(OldP))
		{
			const float R = duration<float>{ Now - Last }.count() * (100.f - NewP);
			Remaining = Remaining ? (Remaining + R) / 2.f : R;
			std::cout << "Progress: " << static_cast<unsigned>(OldP = NewP)
				<< "%\tElapsed: " << FormatDuration(static_cast<unsigned>(duration_cast<seconds>(Now - Start).count()))
				<< "\tRemaining: about " << FormatDuration(static_cast<unsigned>(Remaining), true) << '\n';
			Last = Now;
		}
		Now += 1s;
		for (auto& f : fv)
			f.wait_until(Now);
	}
}

void CreateImageFile(const time_point<system_clock>& Start)
{
	std::vector<std::vector<FColor>> Pixels(GetConfig().Height, std::vector<FColor>{ GetConfig().Width });
	Draw(Pixels, Start);
	std::ofstream OutImageFile{ GetConfig().ImageFileName };
	OutImageFile << "P3\n" << GetConfig().Width << ' ' << GetConfig().Height << "\n255\n";
	for (auto& Row : Pixels)
		for (auto& Pixel : Row)
			OutImageFile << Pixel << '\n';
}

int main()
{
	try
	{
		GetConfig();
		using namespace std::chrono;
		const auto Start = system_clock::now();
		std::cout << "Successfully loaded config file!\n" << GetConfig() << "\n\n";
		CreateImageFile(Start);
		std::cout << '\n' << GetConfig().ImageFileName << " created successfully!\nTime took: "
			<< FormatDuration(static_cast<unsigned>(duration_cast<seconds>(system_clock::now() - Start).count())) << '\n';
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << ". Check the config.ini file.\n";
	}
}
