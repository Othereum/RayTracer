#pragma once
#include <cstdint>
#include <ostream>

struct FColor
{
	uint8_t R, G, B;

	FColor() :R{ 0 }, G{ 0 }, B{ 0 } {}
	FColor(uint8_t R, uint8_t G, uint8_t B) :R{ R }, G{ G }, B{ B } {}
	FColor(const struct FLinearColor& LinearColor);

	static const FColor White;
	static const FColor Black;
	static const FColor Transparent;
	static const FColor Red;
	static const FColor Green;
	static const FColor Blue;
	static const FColor Yellow;
	static const FColor Cyan;
	static const FColor Magenta;
	static const FColor Orange;
	static const FColor Purple;
	static const FColor Turquoise;
	static const FColor Silver;
	static const FColor Emerald;
};

struct FLinearColor
{
	float R, G, B;

	FLinearColor() :R{ 0 }, G{ 0 }, B{ 0 } {}
	FLinearColor(float R, float G, float B) :R{ R }, G{ G }, B{ B } {}

	FLinearColor& operator+=(const FLinearColor& C) { R += C.R; G += C.G; B += C.B; return *this; }
	FLinearColor& operator-=(const FLinearColor& C) { R -= C.R; G -= C.G; B -= C.B; return *this; }
	FLinearColor& operator*=(const FLinearColor& C) { R *= C.R; G *= C.G; B *= C.B; return *this; }
	FLinearColor& operator/=(const FLinearColor& C) { R /= C.R; G /= C.G; B /= C.B; return *this; }
	FLinearColor& operator*=(float Scale) { R *= Scale; G *= Scale; B *= Scale; return *this; }
	FLinearColor& operator/=(float Scale) { R /= Scale; G /= Scale; B /= Scale; return *this; }
	FLinearColor operator+(const FLinearColor& C) const { return { R + C.R, G + C.G, B + C.B }; }
	FLinearColor operator-(const FLinearColor& C) const { return { R - C.R, G - C.G, B - C.B }; }
	FLinearColor operator*(const FLinearColor& C) const { return { R * C.R, G * C.G, B * C.B }; }
	FLinearColor operator/(const FLinearColor& C) const { return { R / C.R, G / C.G, B / C.B }; }
	FLinearColor operator*(float Scale) const { return { R * Scale, G * Scale, B * Scale }; }
	FLinearColor operator/(float Scale) const { return { R / Scale, G / Scale, B / Scale }; }

	static const FLinearColor White;
	static const FLinearColor Gray;
	static const FLinearColor Black;
	static const FLinearColor Transparent;
	static const FLinearColor Red;
	static const FLinearColor Green;
	static const FLinearColor Blue;
	static const FLinearColor Yellow;
};

FLinearColor operator*(float Scale, const FLinearColor& C);
std::ostream& operator<<(std::ostream& S, const FColor& C);
