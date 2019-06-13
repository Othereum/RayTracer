#include <chrono>
#include <fstream>
#include <future>
#include <iostream>
#include <vector>

#include "../Public/Camera.h"
#include "../Public/Color.h"
#include "../Public/Dielectric.h"
#include "../Public/HitableList.h"
#include "../Public/Lambertian.h"
#include "../Public/Math.h"
#include "../Public/Metal.h"
#include "../Public/Ray.h"
#include "../Public/Sphere.h"

using namespace std::chrono;

constexpr auto FileName = "image.ppm";
constexpr unsigned Width = 1920;
constexpr unsigned Height = 1080;
constexpr unsigned NumAASamples = 8192;
constexpr seconds ProgressInterval{ 1 };

constexpr float Ratio = static_cast<float>(Width) / Height;
constexpr unsigned NumPixel = Width * Height;
const unsigned NumThread = std::thread::hardware_concurrency() * 5 / 2;

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

void Draw(std::vector<std::vector<FColor>>& Output, const time_point<system_clock>& Start)
{
	FVector LookFrom{ -3, 13, 2 };
	FVector LookAt{ 0, 0, 0 };
	float DistToFocus = 10;
	float Aperture = .1;
	FCamera Camera{ LookFrom, LookAt, {0.f, 0.f, 1.f}, 20, Ratio, Aperture, DistToFocus };

	HHitableList World;
	World.List.push_back(std::make_unique<HSphere>(FVector{ 0, 0, -1000 }, 1000, std::make_unique<MLambertian>(FLinearColor{ .5f, .5f, .5f })));
	for (int a = -11; a < 11; ++a)
	{
		for (int b = -11; b < 11; ++b)
		{
			float ChooseMat = Math::Rand();
			FVector Center{ a + Math::Rand(0, .9), b + Math::Rand(0, .9), .2 };
			if ((Center - FVector{ 4, .2, 0 }).Size() > .9f)
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
	World.List.push_back(std::make_unique<HSphere>(FVector{ 0, -4, 1 }, 1.f, std::make_unique<MLambertian>(FLinearColor{ .4, .2, .1 })));
	World.List.push_back(std::make_unique<HSphere>(FVector{ 0, 4, 1 }, 1.f, std::make_unique<MMetal>(FLinearColor{ .7, .6, .5 }, 0.f)));

	std::atomic<unsigned> pp = 0;
	auto Draw = [&](unsigned YS, unsigned YE)
	{
		for (unsigned y = YS; y < YE; ++y)
		{
			const float v = (Height - y - 1.f) / Height;
			for (unsigned x = 0; x < Width; ++x)
			{
				const float u = (x * 1.f) / Width;
				FLinearColor Color = GetColor(Camera.GetRay(u, v), World);
				for (unsigned s = 0; s < NumAASamples; ++s)
				{
					Color += GetColor(Camera.GetRay(u + Math::Rand() / Width, v + Math::Rand() / Height), World);
				}
				Color /= NumAASamples + 1;
				Output[y][x] = Color;
				++pp;
			}
		}
	};

	std::vector<std::future<void>> fv;
	fv.reserve(NumThread);
	const unsigned ntr = Height / NumThread;
	for (unsigned i = 0; i < NumThread - 1; ++i)
		fv.push_back(std::async(std::launch::async, Draw, ntr * i, ntr * (i + 1)));
	fv.push_back(std::async(std::launch::async, Draw, ntr * (NumThread-1), Height));
	std::cout << "Created " << NumThread << " parallel tasks.\n\n";
	
	unsigned OldP = 0;
	while (pp < NumPixel)
	{
		unsigned NewP = 100 * pp / NumPixel;
		auto Now = system_clock::now();
		auto Elapsed = duration_cast<seconds>(Now - Start).count();
		if (NewP > OldP)
			std::cout << "Progress: " << (OldP = NewP) << "%\tElapsed: " << Elapsed << "s\tRemaining: " << Elapsed / NewP * (100 - NewP) << "s\n";
		Now += ProgressInterval;
		for (auto& f : fv)
			f.wait_until(Now);
	}
}

void CreateImageFile(const time_point<system_clock>& Start)
{
	std::vector<std::vector<FColor>> Pixels(Height, std::vector<FColor>{ Width });
	Draw(Pixels, Start);
	std::ofstream OutImageFile{ FileName };
	OutImageFile << "P3\n" << Width << ' ' << Height << "\n255\n";
	for (auto& Row : Pixels)
		for (auto& Pixel : Row)
			OutImageFile << Pixel << '\n';
}

int main()
{
	using namespace std::chrono;
	const auto Start = system_clock::now();
	std::cout << "Resolution: " << Width << 'x' << Height << '\n';
	std::cout << "AA samples: " << NumAASamples << "\n\n";
	CreateImageFile(Start);
	std::cout << '\n' << FileName << " created successfully!\nTime took: " << duration<float>{ system_clock::now() - Start }.count() << "s\n";
}
