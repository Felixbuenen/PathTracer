#pragma once

#include "glm/vec3.hpp"

namespace PathTracer {

	typedef glm::vec3 Color;

	struct Ray
	{
		glm::vec3 origin;
		glm::vec3 dir;
		float length;
	};

	/*class Intersection
	{
	public:
		IObject* nearestObj;
		float distance;
		glm::vec3 normal;
	};*/

	const float rayBias = 1e-4f;
	const int MAX_DEPTH = 8;
}