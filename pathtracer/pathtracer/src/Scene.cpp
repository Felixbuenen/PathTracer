#include "Scene.h"

namespace PathTracer {

	Scene::~Scene()
	{
		for (auto obj : m_Objects)
		{
			delete obj;
		}

		m_Objects.clear();
	}

	Color Scene::trace(Ray& ray, int depth) const
	{
		if (depth >= MAX_DEPTH)
		{
			return Color(0, 0, 0);
		}

		// get intersected object
		Intersection intersection = intersect(ray);
		IObject* nearestObj = intersection.nearestObj;

		if (!nearestObj)
		{
			return Color(0, 0, 0); // TODO: sample skybox
		}

		Color color = nearestObj->GetColor();
		return color;
	}

	Intersection Scene::intersect(Ray& ray) const
	{
		Intersection intersect;
		for (auto object : m_Objects) 
		{
			object->intersect(intersect, ray);
			if (intersect.nearestObj)
			{
				return intersect;
			}
		}

		return intersect;
	}
}