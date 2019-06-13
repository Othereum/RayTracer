#include "../Public/Camera.h"
#include "../Public/Math.h"
#include "../Public/Ray.h"

FRay FCamera::GetRay(float S, float T) const
{
	FVector RD = LensRadius * Math::RandomInUnitCircle();
	FVector Offset = U * RD.X + V * RD.Y;
	return { Origin + Offset, LowerLeftCorner + S * Horizontal + T * Vertical - Origin - Offset };
}
