#pragma once

#include "Core.h"

class AssignmentScene_1 : public Scene
{
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