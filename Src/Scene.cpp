#include "Scene.h"

#include <glm/ext.hpp>
#include <glm/glm.hpp>

#include "IntCore.h"

std::string Scene::Name()
{
	return "UNKNOWN";
}

MengerSponge* g_MengerSponge;
std::vector<PointLight> g_PointLights;
int g_NumPointLights = 7;
DirectionalLight g_DirectionalLight;
std::vector<Material> g_Materials;
int g_SceneFlags = LIGHTING_ENABLED;

void Cube::GenerateChildren(int targetDepth)
{
	if (m_Depth == targetDepth)
	{
		m_Children.clear();
		return;
	}

	if (m_Children.size() == 8)
	{
		for (int i = 0; i < 8; i++)
		{
			m_Children[i]->GenerateChildren(targetDepth);
		}
		return;
	}

	m_Children.clear();

	float size = m_Size / 3.0f;
	glm::vec3 min = m_Position - (size);
	glm::vec3 max = m_Position + (size);

	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			for (int z = 0; z < 3; z++)
			{
				if (x % 2 + y % 2 + z % 2 >= 2)
					continue;

				Ref<Cube> newCube = new Cube();
				newCube->m_Depth = m_Depth + 1;
				newCube->m_Position = min + glm::vec3(x * size, y * size, z * size);
				newCube->m_Size = size;

				newCube->GenerateChildren(targetDepth);

				m_Children.push_back(newCube);
			}
}

void MengerSponge::Generate()
{
	GenerateChildren(m_TotalDepth);
}

void Scene::OnStart()
{
}

void Scene::OnStop()
{
}

void Scene::CreateModel()
{
}

void Scene::DestroyModel()
{
}

void Scene::OnSimulate(double DeltaTime)
{
	for (int i = 0; i < m_Entities.size(); i++)
	{
		m_Entities[i]->EOnSimulate(DeltaTime);
	}
}

void Scene::OnRender(double DeltaTime)
{
	for (int i = 0; i < m_Entities.size(); i++)
	{
		m_Entities[i]->EOnRender(DeltaTime);
	}
}

glm::mat4& Scene::GetViewTransform()
{
	return m_ViewTransform;
}

void Scene::SetViewTransform(glm::mat4 transform)
{
	m_ViewTransform = transform;
}

glm::mat4& Scene::GetProjectionTransform()
{
	return m_ProjectionTransform;
}

void Scene::SetProjectionTransform(glm::mat4 transform)
{
	m_ProjectionTransform = transform;
}

void Scene::AddEntity(Entity* entity)
{
	entity->RefInc();
	entity->m_ID = m_NextID++;
	m_Entities.push_back(entity);
}

void Scene::RemoveEntity(Entity* entity)
{
	auto position = std::find(m_Entities.begin(), m_Entities.end(), entity);
	if (position != m_Entities.end())
	{
		m_Entities.erase(position);

		delete entity;
	}
}
