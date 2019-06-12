#include "../Public/Color.h"

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

FColor::FColor(const FLinearColor& LinearColor)
	:R{ static_cast<uint8_t>(sqrt(LinearColor.R) * 255.99999f) },
	G{ static_cast<uint8_t>(sqrt(LinearColor.G) * 255.99999f) },
	B{ static_cast<uint8_t>(sqrt(LinearColor.B) * 255.99999f) }
{
}

FLinearColor operator*(float Scale, const FLinearColor& C)
{
	return C * Scale;
}

std::ostream& operator<<(std::ostream& S, const FColor& C)
{
	return S << static_cast<unsigned>(C.R)
		<< ' ' << static_cast<unsigned>(C.G)
		<< ' ' << static_cast<unsigned>(C.B);
}
