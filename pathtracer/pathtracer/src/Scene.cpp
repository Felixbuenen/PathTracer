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
		IObject* obj = intersect(ray);
		if (obj == nullptr)
		{
			return Color(0, 0, 0); // TODO: sample skybox
		}

		Color color = obj->GetColor();
		return color;
	}

	IObject* Scene::intersect(Ray& ray) const
	{
		for (auto object : m_Objects) 
		{
			if (object->intersect(ray))
			{
				return object;
			}
		}

		return nullptr;
	}
}