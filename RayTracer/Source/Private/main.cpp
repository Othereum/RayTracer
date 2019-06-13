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

constexpr auto FileName = "image.ppm";
constexpr unsigned Width = 512;
constexpr unsigned Height = 256;
constexpr unsigned NumAASamples = 1000;
constexpr std::chrono::seconds ProgressInterval{ 1 };

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

void Draw(std::vector<std::vector<FColor>>& Output)
{
	FCamera Camera;
	Camera.Horizontal.Y = 4.f;
	Camera.Vertical.Z = Camera.Horizontal.Y / Ratio;
	Camera.LowerLeftCorner = { 1.f, Camera.Horizontal.Y * -.5f, Camera.Vertical.Z * -.5f };

	HHitableList World;
	World.List.push_back(std::make_unique<HSphere>(FVector{ 1.f, 0.f, 0.f }, .5f,
		std::make_unique<MLambertian>(FLinearColor{ .1f, .2f, .5f })));
	World.List.push_back(std::make_unique<HSphere>(FVector{ 1.f, 0.f, -100.5f }, 100.f,
		std::make_unique<MLambertian>(FLinearColor{ .8f, .8f, 0.f })));
	World.List.push_back(std::make_unique<HSphere>(FVector{ 1.f, 1.f, 0.f }, .5f,
		std::make_unique<MMetal>(FLinearColor{ .8f, .6f, .2f }, 0.1f)));
	World.List.push_back(std::make_unique<HSphere>(FVector{ 1.f, -1.f, 0.f }, .5f,
		std::make_unique<MDielectric>(1.5f)));
	World.List.push_back(std::make_unique<HSphere>(FVector{ 1.f, -1.f, 0.f }, -.45f,
		std::make_unique<MDielectric>(1.5f)));

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
		if (NewP > OldP)
			std::cout << "Progress: " << (OldP = NewP) << "%\n";
		auto until = std::chrono::system_clock::now() + ProgressInterval;
		for (auto& f : fv)
			f.wait_until(until);
	}
}

void CreateImageFile()
{
	std::vector<std::vector<FColor>> Pixels(Height, std::vector<FColor>{ Width });
	Draw(Pixels);
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
	CreateImageFile();
	std::cout << '\n' << FileName << " created successfully!\nTime took: " << duration<float>{system_clock::now() - Start}.count() << "s\n";
}
