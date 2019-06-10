#include <chrono>
#include <fstream>
#include <iostream>
#include <random>

#include "Camera.h"
#include "Color.h"
#include "HitableList.h"
#include "Math.h"
#include "Ray.h"
#include "Sphere.h"

constexpr auto FileName = "image.ppm";
constexpr unsigned Width = 200;
constexpr unsigned Height = 100;
constexpr unsigned NumAASamples = 100;
constexpr float Ratio = static_cast<float>(Width) / Height;
const FVector SphereLocation{ 1.f, 0.f, 0.f };
constexpr float SphereRadius = .5f;

FLinearColor GetColor(const FRay& Ray, const Hitable& World)
{
	HitRecord Record;
	if (World.Hit(Record, Ray))
	{
		return .5f * (FLinearColor{ Record.Normal.X, Record.Normal.Y, Record.Normal.Z } + FLinearColor::White);
	}

	const FVector NormalDir = FVector::GetNormal(Ray.Dir);
	const float t = .5f * (NormalDir.Z + 1.f);
	return Math::Lerp(FLinearColor::White, { .5f, .7f, 1.f }, t);
}

void Draw(std::ostream& Output)
{
	const FVector Origin{ 0.f, 0.f, 0.f };
	const FVector Horizontal{ 0.f, 4.f, 0.f };
	const FVector Vertical{ 0.f, 0.f, Horizontal.Y / Ratio };
	const FVector LowerLeftCorner{ 1.f, Horizontal.Y * -.5f, Vertical.Z * -.5f };
	const FCamera Camera{ Origin, LowerLeftCorner, Horizontal, Vertical };

	std::vector<std::unique_ptr<Hitable>> List;
	List.push_back(std::make_unique<Sphere>(SphereLocation, SphereRadius));
	List.push_back(std::make_unique<Sphere>(FVector{ 1.f, 0.f, -100.5f }, 100.f));
	HitableList World{ std::move(List) };

	std::uniform_real_distribution<float> fRand;
	std::default_random_engine re{ std::random_device{}() };

	for (unsigned y = 0; y < Height; ++y)
	{
		for (unsigned x = 0; x < Width; ++x)
		{
			FLinearColor Color{ 0.f, 0.f, 0.f };
			for (unsigned s = 0; s < NumAASamples; ++s)
			{
				const float u = (x + fRand(re)) / Width;
				const float v = (Height - y - 1 + fRand(re)) / Height;
				const FRay Ray{ Origin, LowerLeftCorner + u * Horizontal + v * Vertical };
				const FVector P = Ray.PointAtParam(2.f);
				Color += GetColor(Ray, World);
			}
			Color /= NumAASamples;
			Output << FColor{ Color } << '\n';
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
