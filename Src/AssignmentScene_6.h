#pragma once

#include "Core.h"
#include "Shader.h"

class AssignmentScene_6 : public Scene
{
public:
	Ref<Shader> m_Shader;

	GLuint m_VertexArrayObject = 0;
	GLuint m_VertexBufferObject = 0;
	GLuint m_IndexBufferObject = 0;

	std::vector<glm::vec3> m_Target;

	double m_Time;
	int m_TimeDirection = 1;

	unsigned int m_IndexCount = 0;

public:
	void GenerateMesh(Cube* cube, int& offset);

	virtual void CreateModel() override;
	virtual void DestroyModel() override;

	virtual void OnStart() override;
	virtual void OnStop() override;
	virtual void OnSimulate(double DeltaTime) override;
	virtual void OnRender(double DeltaTime) override;

	virtual std::string Name() override;
};