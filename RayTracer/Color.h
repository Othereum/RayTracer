#pragma once

#include <cstdint>
#include <ostream>

struct FLinearColor;
struct FColor
{
	uint8_t R, G, B;

	FColor() :R{ 0 }, G{ 0 }, B{ 0 } {}
	FColor(uint8_t R, uint8_t G, uint8_t B) :R{ R }, G{ G }, B{ B } {}
	FColor(const FLinearColor& LinearColor);
};

struct FLinearColor
{
	float R, G, B;

	FLinearColor() :R{ 0 }, G{ 0 }, B{ 0 } {}
	FLinearColor(float R, float G, float B) :R{ R }, G{ G }, B{ B } {}
	FLinearColor(const FColor& Color) :R{ Color.R / 255.f }, G{ Color.G / 255.f }, B{ Color.B / 255.f } {}
};

FColor::FColor(const FLinearColor& LinearColor)
	:R{ static_cast<uint8_t>(LinearColor.R * 255.99999f) },
	G{ static_cast<uint8_t>(LinearColor.G * 255.99999f) },
	B{ static_cast<uint8_t>(LinearColor.B * 255.99999f) }
{
}

std::ostream& operator<<(std::ostream& S, const FColor& C)
{
	return S << static_cast<unsigned>(C.R)
		<< ' ' << static_cast<unsigned>(C.G)
		<< ' ' << static_cast<unsigned>(C.B);
}