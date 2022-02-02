#pragma once

#include "Core.h"
#include "Shader.h"

class AssignmentScene_3 : public Scene
{
public:
	Ref<Shader> m_Shader;

	std::vector<glm::mat4> m_Transformations;

	GLuint m_VertexArrayObject = 0;
	GLuint m_VertexBufferObject = 0;
	GLuint m_IndexBufferObject = 0;

	unsigned int m_IndexCount = 0;

public:
	void GenerateTransformation(Cube* cube);

	virtual void CreateModel() override;
	virtual void DestroyModel() override;

	virtual void OnStart() override;
	virtual void OnStop() override;
	virtual void OnSimulate(double DeltaTime) override;
	virtual void OnRender(double DeltaTime) override;

	virtual std::string Name() override;
};