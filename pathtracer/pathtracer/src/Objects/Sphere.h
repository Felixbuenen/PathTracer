#pragma once

#include "IObject.h"

namespace PathTracer {

	class Sphere : public IObject
	{
	public:
		Sphere(glm::vec3 position, float radius, Color color, float emittance)
			: m_Pos(position), m_Radius(radius), m_Color(color), m_Emittance(emittance) { }
		
		void intersect(Intersection& outIntersect, Ray& ray) override;

		inline const Color GetColor() const override { return m_Color; };
		inline const float GetEmittance() const override { return m_Emittance; }

	private:
		Color m_Color;
		float m_Emittance;
		glm::vec3 m_Pos;
		float m_Radius;
	};


}