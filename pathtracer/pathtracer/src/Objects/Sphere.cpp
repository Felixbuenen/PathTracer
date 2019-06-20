#include "glm/geometric.hpp"

#include "Sphere.h"

namespace PathTracer {

	bool Sphere::intersect(Ray& ray) const
	{
		glm::vec3 c = m_Pos - ray.origin;
		float t = glm::dot(c, ray.dir);
		glm::vec3 q = c - t * ray.dir;

		float p2 = glm::dot(q, q);
		if (p2 > m_Radius * m_Radius)
		{
			return false;
		}

		return true;
	}
}