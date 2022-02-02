#include "Camera.h"

Ref<CameraType> g_CameraType;

void Camera::EOnCreate()
{
	m_CameraRotation = GetType()->m_CameraRotation;
	m_CameraPosition = GetType()->m_CameraPosition;
}

void Camera::EOnSimulate(double DeltaTime)
{
	if (BindingManager::IsMouseLocked())
	{
		auto [mouseX, mouseY] = BindingManager::GetMouseDelta();

		m_CameraRotation.x += mouseX * DeltaTime * GetType()->MouseSpeed;
		m_CameraRotation.y += -mouseY * DeltaTime * GetType()->MouseSpeed;

		if (m_CameraRotation.y < -89.0)
			m_CameraRotation.y = -89.0;
		if (m_CameraRotation.y > 89.0)
			m_CameraRotation.y = 89.0;

		float scrollAmt = BindingManager::GetValue("mouse_scroll");
		m_SpeedCoef += scrollAmt * DeltaTime * (m_SpeedCoef * 20.0);
	}

	m_SpeedCoef = glm::clamp(m_SpeedCoef, 0.01, 500.0);

	double speed = GetType()->MovementSpeed;

	if (BindingManager::IsMouseLocked() && BindingManager::Get("turbo") >= BindingState::PRESSED)
	{
		speed *= 2.0;
	}

	speed = speed * m_SpeedCoef;

	double forward = 0;
	double strafe = 0;

	if (BindingManager::IsMouseLocked() && BindingManager::Get("forward") >= BindingState::PRESSED)
	{
		forward = -speed;
	}

	if (BindingManager::IsMouseLocked() && BindingManager::Get("backward") >= BindingState::PRESSED)
	{
		forward = speed;
	}

	if (BindingManager::IsMouseLocked() && BindingManager::Get("right") >= BindingState::PRESSED)
	{
		strafe = speed;
	}

	if (BindingManager::IsMouseLocked() && BindingManager::Get("left") >= BindingState::PRESSED)
	{
		strafe = -speed;
	}

	m_Transform[2].x = cos(glm::radians((float)m_CameraRotation.x)) * cos(glm::radians((float)m_CameraRotation.y));
	m_Transform[2].y = sin(glm::radians((float)m_CameraRotation.y));
	m_Transform[2].z = sin(glm::radians((float)m_CameraRotation.x)) * cos(glm::radians((float)m_CameraRotation.y));
	m_Transform[2] = glm::vec4(glm::normalize(glm::vec3(m_Transform[2])), 0.0);
	m_Transform[0] = glm::vec4(glm::normalize(glm::cross(glm::vec3(m_Transform[2]), glm::vec3(0, 1, 0))), 0.0);
	m_Transform[1] = glm::vec4(glm::normalize(glm::cross(glm::vec3(m_Transform[0]), glm::vec3(m_Transform[2]))), 0.0);

	m_CameraPosition += glm::dvec3(m_Transform[0]) * strafe * DeltaTime;
	m_CameraPosition += glm::dvec3(m_Transform[2]) * forward * DeltaTime;

	m_Transform[3] = glm::vec4(m_CameraPosition, 1.0);

	GetScene()->SetViewTransform(glm::inverse(m_Transform));

	GetType()->m_CameraRotation = m_CameraRotation;
	GetType()->m_CameraPosition = m_CameraPosition;
}
