#include "glm/geometric.hpp"

#include "Sphere.h"

namespace PathTracer {

	void Sphere::intersect(Intersection& outIntersect, Ray& ray)
	{
		glm::vec3 c = m_Pos - ray.origin;
		float t = glm::dot(c, ray.dir);
		ray.length = t;
		glm::vec3 q = c - t * ray.dir;

		float p2 = glm::dot(q, q);
		if (p2 > m_Radius * m_Radius)
		{
			return;
		}

		t -= glm::sqrt(m_Radius * m_Radius - p2);
		if (t < ray.length && t > 0)
		{
			glm::vec3 normal = glm::normalize(ray.dir * t - c);

			outIntersect.distance = t;
			outIntersect.nearestObj = this;
			outIntersect.normal = normal;
		}
	}
}