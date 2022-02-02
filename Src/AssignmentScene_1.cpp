#include "AssignmentScene_1.h"

#include "Camera.h"

void AssignmentScene_1::OnStart()
{
	Scene::OnStart();

	SpawnEntity<Camera>(g_CameraType);


	CreateModel();

	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void AssignmentScene_1::OnStop()
{
	DestroyModel();

	glDisable(GL_LIGHTING);

	for (int i = 0; i < g_NumPointLights + 1; i++)
	{
		glDisable(GL_LIGHT0 + i);
	}

	Scene::OnStop();
}

void AssignmentScene_1::GenerateMesh(Cube* cube, int& offset)
{
	for (int i = 0; i < cube->m_Children.size(); i++)
	{
		GenerateMesh(cube->m_Children[i], offset);
	}

	if (cube->m_Children.size() != 0)
		return;

	static glm::vec3 points[48] = {
		glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f),

		glm::vec3(+0.5f, +0.5f, +0.5f), glm::vec3(+0.5f, -0.5f, +0.5f), glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(+0.5f, +0.5f, +0.5f),

		glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(-0.5f, -0.5f, -0.5f),

		glm::vec3(+0.5f, +0.5f, +0.5f), glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(+0.5f, -0.5f, +0.5f), glm::vec3(+0.5f, +0.5f, +0.5f),

		glm::vec3(+0.5f, -0.5f, +0.5f), glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(+0.5f, -0.5f, +0.5f),

		glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(+0.5f, +0.5f, +0.5f), glm::vec3(+0.5f, +0.5f, +0.5f), glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(-0.5f, +0.5f, -0.5f),
	};

	static int materials[48] = {
		0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1,
		2, 2, 2, 2, 2, 2,
		3, 3, 3, 3, 3, 3,
		4, 4, 4, 4, 4, 4,
		5, 5, 5, 5, 5, 5,

	};

	static glm::vec3 normals[48] = {
		glm::vec3(+0.0f, +0.0f, -1.0f), glm::vec3(+0.0f, +0.0f, -1.0f), glm::vec3(+0.0f, +0.0f, -1.0f), glm::vec3(+0.0f, +0.0f, -1.0f), glm::vec3(+0.0f, +0.0f, -1.0f), glm::vec3(+0.0f, +0.0f, -1.0f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, +0.0f, +1.0f),
		glm::vec3(-1.0f, +0.0f, +0.0f), glm::vec3(-1.0f, +0.0f, +0.0f), glm::vec3(-1.0f, +0.0f, +0.0f), glm::vec3(-1.0f, +0.0f, +0.0f), glm::vec3(-1.0f, +0.0f, +0.0f), glm::vec3(-1.0f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f),
		glm::vec3(+0.0f, -1.0f, +0.0f), glm::vec3(+0.0f, -1.0f, +0.0f), glm::vec3(+0.0f, -1.0f, +0.0f), glm::vec3(+0.0f, -1.0f, +0.0f), glm::vec3(+0.0f, -1.0f, +0.0f), glm::vec3(+0.0f, -1.0f, +0.0f), glm::vec3(+0.0f, +1.0f, +0.0f), glm::vec3(+0.0f, +1.0f, +0.0f), glm::vec3(+0.0f, +1.0f, +0.0f), glm::vec3(+0.0f, +1.0f, +0.0f), glm::vec3(+0.0f, +1.0f, +0.0f), glm::vec3(+0.0f, +1.0f, +0.0f),
	};

	for (int i = 0; i < 48; i++)
	{
		m_Positions.push_back((points[i] * cube->m_Size) + cube->m_Position);
		m_Normals.push_back(glm::normalize(normals[i]));
		m_Materials.push_back(materials[i]);
	}

	for (int i = 0; i < 48; i++)
	{
		m_Indices.push_back(offset + i);
	}

	offset += 48;
}

void AssignmentScene_1::CreateModel()
{
	Scene::CreateModel();

	m_Positions.clear();
	m_Normals.clear();
	m_Indices.clear();
	int offset = 0;

	GenerateMesh(g_MengerSponge, offset);
}

void AssignmentScene_1::DestroyModel()
{
	Scene::DestroyModel();
}

void AssignmentScene_1::OnSimulate(double DeltaTime)
{
	Scene::OnSimulate(DeltaTime);
}

void AssignmentScene_1::OnRender(double DeltaTime)
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(m_ProjectionTransform));

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glMultMatrixf(glm::value_ptr(m_ViewTransform));

	for (int i = 0; i < 8; i++)
		glDisable(GL_LIGHT0 + i);

	float light_position[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float light_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float light_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	float mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	bool lightingEnabled = g_SceneFlags & LIGHTING_ENABLED;

	if (lightingEnabled)
	{
		{
			light_position[0] = -g_DirectionalLight.direction.x;
			light_position[1] = -g_DirectionalLight.direction.y;
			light_position[2] = -g_DirectionalLight.direction.z;
			light_position[3] = 0.f;

			light_ambient[0] = g_DirectionalLight.ambient.x;
			light_ambient[1] = g_DirectionalLight.ambient.y;
			light_ambient[2] = g_DirectionalLight.ambient.z;

			light_diffuse[0] = g_DirectionalLight.diffuse.x;
			light_diffuse[1] = g_DirectionalLight.diffuse.y;
			light_diffuse[2] = g_DirectionalLight.diffuse.z;

			light_specular[0] = g_DirectionalLight.specular.x;
			light_specular[1] = g_DirectionalLight.specular.y;
			light_specular[2] = g_DirectionalLight.specular.z;

			int lightIdx = GL_LIGHT0;
			glEnable(lightIdx);
			glLightfv(lightIdx, GL_POSITION, light_position);
			glLightfv(lightIdx, GL_AMBIENT, light_ambient);
			glLightfv(lightIdx, GL_DIFFUSE, light_diffuse);
			glLightfv(lightIdx, GL_SPECULAR, light_specular);
		}

		for (int i = 0; i < g_NumPointLights; i++)
		{
			const auto& light = g_PointLights[i];

			light_position[0] = light.position.x;
			light_position[1] = light.position.y;
			light_position[2] = light.position.z;
			light_position[3] = 1.f;

			light_ambient[0] = light.ambient.x;
			light_ambient[1] = light.ambient.y;
			light_ambient[2] = light.ambient.z;

			light_diffuse[0] = light.diffuse.x;
			light_diffuse[1] = light.diffuse.y;
			light_diffuse[2] = light.diffuse.z;

			light_specular[0] = light.specular.x;
			light_specular[1] = light.specular.y;
			light_specular[2] = light.specular.z;

			int lightIdx = GL_LIGHT1 + i;
			glEnable(lightIdx);
			glLightfv(lightIdx, GL_POSITION, light_position);
			glLightfv(lightIdx, GL_AMBIENT, light_ambient);
			glLightfv(lightIdx, GL_DIFFUSE, light_diffuse);
			glLightfv(lightIdx, GL_SPECULAR, light_specular);

			glLightf(lightIdx, GL_CONSTANT_ATTENUATION, light.constant);
			glLightf(lightIdx, GL_LINEAR_ATTENUATION, light.linear);
			glLightf(lightIdx, GL_QUADRATIC_ATTENUATION, light.quadratic);
		}
	}

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < m_Indices.size(); i++)
	{
		int index = m_Indices[i];
		glm::vec3 position = m_Positions[index];
		glm::vec3 normal = m_Normals[index];
		Material material = g_Materials[m_Materials[index]];

		mat_ambient[0] = material.ambient.x;
		mat_ambient[1] = material.ambient.y;
		mat_ambient[2] = material.ambient.z;

		mat_diffuse[0] = material.diffuse.x;
		mat_diffuse[1] = material.diffuse.y;
		mat_diffuse[2] = material.diffuse.z;

		mat_specular[0] = material.specular.x;
		mat_specular[1] = material.specular.y;
		mat_specular[2] = material.specular.z;

		if (lightingEnabled)
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMaterialf(GL_FRONT, GL_SHININESS, sqrtf(material.shininess));
		}
		else
		{
			glColor3f(material.ambient.x + material.diffuse.x, material.ambient.y + material.diffuse.y, material.ambient.z + material.diffuse.z);
		}

		glNormal3f(normal.x, normal.y, normal.z);

		glVertex3f(position.x, position.y, position.z);
	}

	glEnd();

	glPopMatrix();
}

std::string AssignmentScene_1::Name()
{
	return "Scene 1";
}
