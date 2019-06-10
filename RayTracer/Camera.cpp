#include "Camera.h"
#include "Ray.h"

FRay FCamera::GetRay(float U, float V) const
{
	return FRay{ Origin, LowerLeftCorner + U * Horizontal + V * Vertical };
}
