#pragma once

#include "Core.h"

class CameraType : public EntityType
{
public:
	float MovementSpeed = 5.0f;
	float MouseSpeed = 45.0f * 0.5f;

	glm::dvec3 m_CameraPosition;
	glm::dvec3 m_CameraRotation;
};

extern Ref<CameraType> g_CameraType;

class Camera : public Entity
{
	glm::dvec3 m_CameraPosition;
	glm::dvec3 m_CameraRotation;

	double m_SpeedCoef = 1.0f;

public:
	ENTITY_CONSTRUCTOR(Camera)

	virtual void EOnCreate() override;
	virtual void EOnSimulate(double DeltaTime) override;
};