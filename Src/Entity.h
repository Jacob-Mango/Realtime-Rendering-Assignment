#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Entity.h"
#include "IntCore.h"

#define ENTITY_CONSTRUCTOR(T)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      \
	Ref<##T##Type> GetType()                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       \
	{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              \
		return Entity::GetType().As<##T##Type>();                                                                                                                                                                                                                                                                                                                                                                                                                                                                  \
	}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              \
	T() : T(new T##Type())                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         \
	{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              \
	}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              \
	T(Ref<T##Type> type) : Entity(type.As<EntityType>())                                                                                                                                                                                                                                                                                                                                                                                                                                                           \
	{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              \
	}

#define ENTITY_CONSTRUCTOR_BASE(T, BASE)                                                                                                                                                                                                                                                                                                                                                                                                                                                                           \
	typedef BASE super;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            \
	Ref<##T##Type> GetType()                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       \
	{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              \
		return BASE::GetType().As<##T##Type>();                                                                                                                                                                                                                                                                                                                                                                                                                                                                    \
	}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              \
	T() : T(new T##Type())                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         \
	{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              \
	}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              \
	T(Ref<T##Type> type) : BASE(type.As<EntityType>())                                                                                                                                                                                                                                                                                                                                                                                                                                                             \
	{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              \
	}

class Scene;

class EntityType : public Countable
{
};

class Entity : public Countable
{
	friend Scene;

private:
	unsigned int m_ID = 0;

	Scene* m_Scene = nullptr;

	Ref<Entity> m_Parent;
	std::vector<Entity*> m_Children;

	Ref<EntityType> m_Type;

	bool m_IsDeleting = false;

protected:
	glm::mat4 m_Transform;

public:
	Entity(Ref<EntityType> type);
	virtual ~Entity();

	void Delete();

	void AddChild(Ref<Entity> child);
	void RemoveChild(Ref<Entity> child);
	Ref<Entity> GetParent();

	void SetTransform(glm::mat4 transform);
	glm::mat4 GetTransform();

	void SetScene(Scene* Scene);
	Scene* GetScene();

	Ref<EntityType> GetType();

	virtual void EOnCreate();
	virtual void EOnSimulate(double DeltaTime);
	virtual void EOnRender(double DeltaTime);
};
