// Copyright (c) 2019, Othereum. All rights reserved.
#pragma once

namespace Math
{
	template <class T>
	T Lerp(const T& A, const T& B, float t)
	{
		return (1.f - t) * A + t * B;
	}
}
