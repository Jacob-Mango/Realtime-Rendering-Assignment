#include "Entity.h"

#include "Scene.h"

Entity::Entity(Ref<EntityType> type) : m_Type(type)
{
	m_Transform = glm::mat4(1.0f);
}

Entity::~Entity()
{
	if (!m_IsDeleting)
		std::cerr << "Entity being deleted without being called by Entity::Delete!" << std::endl;
}

void Entity::AddChild(Ref<Entity> child)
{
	if (child->m_Parent != nullptr)
	{
		if (child->m_Parent == this)
			return;

		child->m_Parent->RemoveChild(child);
	}

	child->m_Parent = this;
	m_Children.push_back(child);
}

void Entity::Delete()
{
	m_IsDeleting = true;

	if (m_Children.size() > 0)
		for (size_t i = m_Children.size() - 1; i >= 0; i--)
		{
			RemoveChild(m_Children[i]);
		}

	m_Scene->RemoveEntity(this);
}

void Entity::RemoveChild(Ref<Entity> child)
{
	for (size_t i = 0; i < m_Children.size(); i++)
	{
		if (m_Children[i] != child)
			continue;

		child->m_Parent = nullptr;
		m_Children.erase(m_Children.begin() + i);
	}
}

Ref<Entity> Entity::GetParent()
{
	return m_Parent;
}

void Entity::SetTransform(glm::mat4 transform)
{
	m_Transform = transform;
}

glm::mat4 Entity::GetTransform()
{
	return m_Transform;
}

void Entity::SetScene(Scene* Scene)
{
	m_Scene = Scene;
}

Scene* Entity::GetScene()
{
	return m_Scene;
}

void Entity::EOnCreate()
{
}

void Entity::EOnSimulate(double DeltaTime)
{
}

void Entity::EOnRender(double DeltaTime)
{
}

Ref<EntityType> Entity::GetType()
{
	return m_Type;
}
