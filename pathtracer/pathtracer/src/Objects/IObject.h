#pragma once

#include "../Defines.h"

namespace PathTracer {

	class IObject
	{
	public:
		IObject() {}
		virtual void intersect(Intersection& outIntersect, Ray& ray) = 0;

		virtual const Color GetColor() const = 0;
		virtual const float GetEmittance() const = 0;
	};

}

