#pragma once

#include "IntCore.h"

#include "Entity.h"

class Cube : public Countable
{
public:
	glm::vec3 m_Position = glm::vec3(0, 0, 0);
	float m_Size = 1.0f;
	unsigned int m_Depth = 0;

	std::vector<Ref<Cube>> m_Children;

	Cube()
	{
	}

	Cube(const Cube& other)
	{
		m_Position = other.m_Position;
		m_Size = other.m_Size;
		m_Depth = other.m_Depth;
		m_Children = other.m_Children;
	}

	void GenerateChildren(int targetDepth);
};

class MengerSponge : public Cube
{
public:
	int m_TotalDepth = 1;
	int m_PreviousTotalDepth = 0;

	void Generate();
};

extern MengerSponge* g_MengerSponge;

struct DirectionalLight
{
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct PointLight
{
	glm::vec3 position;

	float constant;
	float linear;
	float quadratic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

extern std::vector<PointLight> g_PointLights;
extern int g_NumPointLights;

#define LIGHTING_ENABLED 0b0001
#define USE_DYNAMIC_DRAW 0b0010

extern int g_SceneFlags;

extern DirectionalLight g_DirectionalLight;

struct Material
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

extern std::vector<Material> g_Materials;

class Application;
class Entity;
class EntityType;

class Scene : public Countable
{
public:
	friend class Entity;

#define SIZE_OF(X, Y) X.size() * sizeof(Y)

	std::vector<glm::vec3> m_Positions;
	std::vector<glm::vec3> m_Normals;
	std::vector<unsigned int> m_Materials;
	std::vector<unsigned int> m_Indices;

private:
	std::vector<Entity*> m_Entities;

	unsigned int m_NextID = 0;

protected:
	glm::mat4 m_ViewTransform;
	glm::mat4 m_ProjectionTransform;

public:
	virtual std::string Name();

	virtual void CreateModel();
	virtual void DestroyModel();

	virtual void OnStart();
	virtual void OnStop();
	virtual void OnSimulate(double DeltaTime);
	virtual void OnRender(double DeltaTime);

	template <typename T> Ref<T> SpawnEntity()
	{
		Ref<T> ent = new T();
		ent->SetScene(this);

		AddEntity(ent);

		ent->EOnCreate();

		return ent;
	}

	template <typename T, typename T2> Ref<T> SpawnEntity(Ref<T2> type)
	{
		Ref<T> ent = new T(type);
		ent->SetScene(this);

		AddEntity(ent);

		ent->EOnCreate();

		return ent;
	}

	glm::mat4& GetViewTransform();
	void SetViewTransform(glm::mat4 transform);

	glm::mat4& GetProjectionTransform();
	void SetProjectionTransform(glm::mat4 transform);

private:
	void AddEntity(Entity* entity);

	void RemoveEntity(Entity* entity);
};
