#include "AssignmentScene_4.h"

#include "Camera.h"

void AssignmentScene_4::OnStart()
{
	Scene::OnStart();

	SpawnEntity<Camera>(g_CameraType);

	m_Shader = new Shader("shaders/instance.vs", "shaders/lighting.fs");

	static glm::vec3 points[36] = {
		glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f),

		glm::vec3(+0.5f, +0.5f, +0.5f), glm::vec3(+0.5f, -0.5f, +0.5f), glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(+0.5f, +0.5f, +0.5f),

		glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(-0.5f, -0.5f, -0.5f),

		glm::vec3(+0.5f, +0.5f, +0.5f), glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(+0.5f, -0.5f, +0.5f), glm::vec3(+0.5f, +0.5f, +0.5f),

		glm::vec3(+0.5f, -0.5f, +0.5f), glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(+0.5f, -0.5f, +0.5f),

		glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(+0.5f, +0.5f, +0.5f), glm::vec3(+0.5f, +0.5f, +0.5f), glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(-0.5f, +0.5f, -0.5f),
	};

	static int materials[36] = {
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5,
	};

	static glm::vec3 normals[36] = {
		glm::vec3(+0.0f, +0.0f, -1.0f), glm::vec3(+0.0f, +0.0f, -1.0f), glm::vec3(+0.0f, +0.0f, -1.0f), glm::vec3(+0.0f, +0.0f, -1.0f), glm::vec3(+0.0f, +0.0f, -1.0f), glm::vec3(+0.0f, +0.0f, -1.0f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, +0.0f, +1.0f),
		glm::vec3(-1.0f, +0.0f, +0.0f), glm::vec3(-1.0f, +0.0f, +0.0f), glm::vec3(-1.0f, +0.0f, +0.0f), glm::vec3(-1.0f, +0.0f, +0.0f), glm::vec3(-1.0f, +0.0f, +0.0f), glm::vec3(-1.0f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f),
		glm::vec3(+0.0f, -1.0f, +0.0f), glm::vec3(+0.0f, -1.0f, +0.0f), glm::vec3(+0.0f, -1.0f, +0.0f), glm::vec3(+0.0f, -1.0f, +0.0f), glm::vec3(+0.0f, -1.0f, +0.0f), glm::vec3(+0.0f, -1.0f, +0.0f), glm::vec3(+0.0f, +1.0f, +0.0f), glm::vec3(+0.0f, +1.0f, +0.0f), glm::vec3(+0.0f, +1.0f, +0.0f), glm::vec3(+0.0f, +1.0f, +0.0f), glm::vec3(+0.0f, +1.0f, +0.0f), glm::vec3(+0.0f, +1.0f, +0.0f),
	};

	for (int i = 0; i < 36; i++)
	{
		m_Positions.push_back(points[i]);
		m_Normals.push_back(glm::normalize(normals[i]));
		m_Materials.push_back(materials[i]);
	}

	for (int i = 0; i < 36; i++)
	{
		m_Indices.push_back(i);
	}

	glGenVertexArrays(1, &m_VertexArrayObject);
	glBindVertexArray(m_VertexArrayObject);

	glGenBuffers(1, &m_VertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, SIZE_OF(m_Positions, glm::vec3) + SIZE_OF(m_Normals, glm::vec3) + SIZE_OF(m_Materials, unsigned int), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &m_IndexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, SIZE_OF(m_Indices, unsigned int), m_Indices.data(), GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, SIZE_OF(m_Positions, glm::vec3), m_Positions.data());
	glBufferSubData(GL_ARRAY_BUFFER, SIZE_OF(m_Positions, glm::vec3), SIZE_OF(m_Normals, glm::vec3), m_Normals.data());
	glBufferSubData(GL_ARRAY_BUFFER, SIZE_OF(m_Positions, glm::vec3) + SIZE_OF(m_Normals, glm::vec3), SIZE_OF(m_Materials, unsigned int), m_Materials.data());

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(SIZE_OF(m_Positions, glm::vec3)));

	glEnableVertexAttribArray(2);
	glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, sizeof(int), (void*)(SIZE_OF(m_Positions, glm::vec3) + SIZE_OF(m_Normals, glm::vec3)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_IndexCount = (unsigned int)m_Indices.size();

	CreateModel();
}

void AssignmentScene_4::OnStop()
{
	m_Shader = nullptr;
	Scene::OnStop();

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_VertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_VertexBufferObject);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_IndexBufferObject);

	DestroyModel();

	m_Positions.clear();
	m_Normals.clear();
	m_Materials.clear();
	m_Indices.clear();
}

void AssignmentScene_4::DestroyModel()
{
	m_Transformations.clear();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_InstanceBufferObject);
}

void AssignmentScene_4::GenerateTransformation(Cube* cube)
{
	for (int i = 0; i < cube->m_Children.size(); i++)
	{
		GenerateTransformation(cube->m_Children[i]);
	}

	if (cube->m_Children.size() != 0)
		return;

	glm::mat4 transformation(1.0f);

	transformation = glm::translate(transformation, cube->m_Position);
	transformation = glm::scale(transformation, glm::vec3(cube->m_Size));

	m_Transformations.push_back(transformation);
}

void AssignmentScene_4::CreateModel()
{
	Scene::CreateModel();

	GenerateTransformation(g_MengerSponge);

	glBindVertexArray(m_VertexArrayObject);

	glGenBuffers(1, &m_InstanceBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_InstanceBufferObject);
	glBufferData(GL_ARRAY_BUFFER, m_Transformations.size() * sizeof(glm::mat4), &m_Transformations[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void AssignmentScene_4::OnSimulate(double DeltaTime)
{
	Scene::OnSimulate(DeltaTime);
}

void AssignmentScene_4::OnRender(double DeltaTime)
{
	m_Shader->Bind();

	m_Shader->Set("u_ProjectionMatrix", m_ProjectionTransform);
	m_Shader->Set("u_ViewMatrix", m_ViewTransform);

	m_Shader->Set("u_CameraPosition", glm::vec3(glm::inverse(m_ViewTransform)[3]));

	for (int i = 0; i < g_Materials.size(); i++)
	{
		m_Shader->Set("u_Materials[" + std::to_string(i) + "].ambient", g_Materials[i].ambient);
		m_Shader->Set("u_Materials[" + std::to_string(i) + "].diffuse", g_Materials[i].diffuse);
		m_Shader->Set("u_Materials[" + std::to_string(i) + "].specular", g_Materials[i].specular);
		m_Shader->Set("u_Materials[" + std::to_string(i) + "].shininess", g_Materials[i].shininess);
	}

	bool lightingEnabled = g_SceneFlags & LIGHTING_ENABLED;
	m_Shader->Set("u_LightingEnabled", lightingEnabled);

	m_Shader->Set("u_DirectionalLight.direction", g_DirectionalLight.direction);
	m_Shader->Set("u_DirectionalLight.ambient", g_DirectionalLight.ambient);
	m_Shader->Set("u_DirectionalLight.diffuse", g_DirectionalLight.diffuse);
	m_Shader->Set("u_DirectionalLight.specular", g_DirectionalLight.specular);

	m_Shader->Set("u_NumPointLights", g_NumPointLights);

	for (int i = 0; i < g_NumPointLights; i++)
	{
		m_Shader->Set("u_PointLights[" + std::to_string(i) + "].position", g_PointLights[i].position);
		m_Shader->Set("u_PointLights[" + std::to_string(i) + "].constant", g_PointLights[i].constant);
		m_Shader->Set("u_PointLights[" + std::to_string(i) + "].linear", g_PointLights[i].linear);
		m_Shader->Set("u_PointLights[" + std::to_string(i) + "].quadratic", g_PointLights[i].quadratic);
		m_Shader->Set("u_PointLights[" + std::to_string(i) + "].ambient", g_PointLights[i].ambient);
		m_Shader->Set("u_PointLights[" + std::to_string(i) + "].diffuse", g_PointLights[i].diffuse);
		m_Shader->Set("u_PointLights[" + std::to_string(i) + "].specular", g_PointLights[i].specular);
	}

	glm::vec3 dir[6] = {glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(-1, 0, 0), glm::vec3(0, -1, 0), glm::vec3(0, 0, -1)};
	int dirI = 0;

	for (int i = 0; i < m_Transformations.size(); i++)
	{
		if (dirI >= 6)
			dirI = 0;
		glm::mat4 transform = m_Transformations[i];
		transform = glm::rotate(transform, 2.0f * (float)DeltaTime, dir[dirI++]);
		m_Transformations[i] = transform;
	}

	glBindVertexArray(m_VertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, m_InstanceBufferObject);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_Transformations.size() * sizeof(glm::mat4), &m_Transformations[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)m_IndexCount, GL_UNSIGNED_INT, 0, (GLsizei)m_Transformations.size());
	glBindVertexArray(0);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		std::cerr << "[OpenGL Error] (" << std::to_string(error) << "): "
				  << "\t" << __FILE__ << ":" << __LINE__ << std::endl;

	m_Shader->Unbind();
}

std::string AssignmentScene_4::Name()
{
	return "Scene 4";
}
