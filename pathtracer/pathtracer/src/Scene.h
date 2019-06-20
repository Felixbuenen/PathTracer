#pragma once

#include <vector>

#include "Defines.h"
#include "Objects/IObject.h"

namespace PathTracer {

	class Scene
	{
	public:
		Scene(std::vector<IObject*> objects)
			: m_Objects(objects) {}
		~Scene();

		Color trace(Ray& ray, int depth) const;
		Intersection intersect(Ray& ray) const;

	private:
		std::vector<IObject*> m_Objects;
	};

}