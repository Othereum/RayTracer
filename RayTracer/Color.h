// Copyright (c) 2019, Othereum. All rights reserved.
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
	FLinearColor(const FColor& Color) :R{ Color.R / 255.f }, G{ Color.G / 255.f }, B{ Color.B / 255.f } {}

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

FLinearColor operator*(float Scale, const FLinearColor& C)
{
	return C * Scale;
}

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

const FLinearColor FLinearColor::White(1.f, 1.f, 1.f);
const FLinearColor FLinearColor::Gray(0.5f, 0.5f, 0.5f);
const FLinearColor FLinearColor::Black(0, 0, 0);
const FLinearColor FLinearColor::Red(1.f, 0, 0);
const FLinearColor FLinearColor::Green(0, 1.f, 0);
const FLinearColor FLinearColor::Blue(0, 0, 1.f);
const FLinearColor FLinearColor::Yellow(1.f, 1.f, 0);

const FColor FColor::White(255, 255, 255);
const FColor FColor::Black(0, 0, 0);
const FColor FColor::Red(255, 0, 0);
const FColor FColor::Green(0, 255, 0);
const FColor FColor::Blue(0, 0, 255);
const FColor FColor::Yellow(255, 255, 0);
const FColor FColor::Cyan(0, 255, 255);
const FColor FColor::Magenta(255, 0, 255);
const FColor FColor::Orange(243, 156, 18);
const FColor FColor::Purple(169, 7, 228);
const FColor FColor::Turquoise(26, 188, 156);
const FColor FColor::Silver(189, 195, 199);
const FColor FColor::Emerald(46, 204, 113);