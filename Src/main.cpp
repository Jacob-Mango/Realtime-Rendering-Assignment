#define GLT_IMPLEMENTATION
#include "Application.h"

#include "Binding.h"
#include "Camera.h"

#include "AssignmentScene_1.h"
#include "AssignmentScene_2.h"
#include "AssignmentScene_3.h"
#include "AssignmentScene_4.h"
#include "AssignmentScene_5.h"
#include "AssignmentScene_6.h"

struct TestState
{
	int m_Scene;
	int m_Subdivision;
	bool m_DepthTesting;
	bool m_BackFaceCulling;
	int m_SceneFlags;
	int m_NumLights;
};

class Assignment_1 : public Application
{
private:
	bool m_WasMouseLocked = false;
	int m_FaceMode = GL_FILL;
	bool m_DepthTesting = true;
	bool m_BackFaceCulling = true;
	bool m_OSDMode = false;

	std::vector<GLTtext*> m_Texts;
	Uint64 m_LastFrame = 0;
	Uint64 m_LastTime = 0;

	std::vector<Ref<Scene>> m_Scenes;

	std::vector<TestState> m_Test;
	int m_TestIndex = -1;

public:
	Assignment_1(const char* title, bool fullscreen = false, int width = 1024, int height = 768) : Application(title, fullscreen, width, height)
	{
	}

	int Init();

	virtual void OnStart() override;
	virtual void OnTick(double DeltaTime) override;

	void AddScene(Ref<Scene> scene);
	void LoadScene(int num);

	void UpdateOSD(double avgFPS);

	void UpdateTest(double avgFPS);
	bool StartTest(int index);
};

int Assignment_1::Init()
{
	g_CameraType = new CameraType();
	g_CameraType->m_CameraPosition = glm::vec3(2, 0, 0);

	if (int err = Application::Init() != 1)
	{
		return err;
	}

	SetVsync(true);

	BindingManager::RegisterCombos("exit", {{{27, BindingType::KEY}}});
	BindingManager::RegisterCombos("focus", {{{1, BindingType::MOUSE}}});

	BindingManager::RegisterCombos("forward", {{{'w', BindingType::KEY}}});
	BindingManager::RegisterCombos("backward", {{{'s', BindingType::KEY}}});
	BindingManager::RegisterCombos("left", {{{'a', BindingType::KEY}}});
	BindingManager::RegisterCombos("right", {{{'d', BindingType::KEY}}});

	BindingManager::RegisterCombos("toggle_facemode", {{{'f', BindingType::KEY}}});
	BindingManager::RegisterCombos("toggle_backfaceculling", {{{'c', BindingType::KEY}}});
	BindingManager::RegisterCombos("toggle_depthtesting", {{{'z', BindingType::KEY}}});
	BindingManager::RegisterCombos("toggle_osd", {{{'h', BindingType::KEY}}});
	BindingManager::RegisterCombos("toggle_vsync", {{{'v', BindingType::KEY}}});
	BindingManager::RegisterCombos("toggle_light", {{{'l', BindingType::KEY}}});

	BindingManager::RegisterCombos("turbo", {{{SDLK_LSHIFT, BindingType::KEY}}});
	BindingManager::RegisterCombos("mouse_scroll", {{{MOUSE_WHEEL_UP, BindingType::MOUSE}, {MOUSE_WHEEL_DOWN, BindingType::MOUSE}}});

	BindingManager::RegisterCombos("subdiv_decrease", {{{'-', BindingType::KEY}}, {{SDLK_KP_MINUS, BindingType::KEY}}});
	BindingManager::RegisterCombos("subdiv_increase", {{{'=', BindingType::KEY}}, {{SDLK_KP_PLUS, BindingType::KEY}}});

	BindingManager::RegisterCombos("light_decrease", {{{',', BindingType::KEY}}});
	BindingManager::RegisterCombos("light_increase", {{{'.', BindingType::KEY}}});

	BindingManager::RegisterCombos("scene_1", {{{'1', BindingType::KEY}}});
	BindingManager::RegisterCombos("scene_2", {{{'2', BindingType::KEY}}});
	BindingManager::RegisterCombos("scene_3", {{{'3', BindingType::KEY}}});
	BindingManager::RegisterCombos("scene_4", {{{'4', BindingType::KEY}}});
	BindingManager::RegisterCombos("scene_5", {{{'5', BindingType::KEY}}});
	BindingManager::RegisterCombos("scene_6", {{{'6', BindingType::KEY}}});

	if (!gltInit())
	{
		std::cerr << "Warning: Failed to initialize glText" << std::endl;
		return 0;
	}

	g_MengerSponge = new MengerSponge();
	g_MengerSponge->Generate();

	g_NumPointLights = 7;
	const float LIGHT_DISTANCE = 1.2f;
	g_PointLights.push_back({glm::vec3(0.0f, 0.0f, 0.0f) * LIGHT_DISTANCE, 0.0f, 0.7f, 2.2f, glm::vec3(0.001f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.2f)});
	g_PointLights.push_back({glm::vec3(1.0f, 0.0f, 0.0f) * LIGHT_DISTANCE, 0.1f, 0.3f, 0.32f, glm::vec3(0.001f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.2f)});
	g_PointLights.push_back({glm::vec3(0.0f, 1.0f, 0.0f) * LIGHT_DISTANCE, 0.1f, 0.3f, 0.32f, glm::vec3(0.001f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.2f)});
	g_PointLights.push_back({glm::vec3(0.0f, 0.0f, 1.0f) * LIGHT_DISTANCE, 0.1f, 0.3f, 0.32f, glm::vec3(0.001f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.2f)});
	g_PointLights.push_back({glm::vec3(-1.0f, 0.0f, 0.0f) * LIGHT_DISTANCE, 0.1f, 0.3f, 0.32f, glm::vec3(0.001f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.2f)});
	g_PointLights.push_back({glm::vec3(0.0f, -1.0f, 0.0f) * LIGHT_DISTANCE, 0.1f, 0.3f, 0.32f, glm::vec3(0.001f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.2f)});
	g_PointLights.push_back({glm::vec3(0.0f, 0.0f, -1.0f) * LIGHT_DISTANCE, 0.1f, 0.3f, 0.32f, glm::vec3(0.001f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.2f)});

	g_DirectionalLight.ambient = glm::vec3(0.001f);
	g_DirectionalLight.diffuse = glm::vec3(1.0f);
	g_DirectionalLight.specular = glm::vec3(0.5f);

	g_Materials.push_back({glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f), 4.f});
	g_Materials.push_back({glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 4.f});
	g_Materials.push_back({glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f), 4.f});
	g_Materials.push_back({glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f), 4.f});
	g_Materials.push_back({glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f), 4.f});
	g_Materials.push_back({glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(1.0f), 4.f});

	AddScene(new AssignmentScene_1());
	AddScene(new AssignmentScene_2());
	AddScene(new AssignmentScene_3());
	AddScene(new AssignmentScene_4());
	AddScene(new AssignmentScene_5());
	AddScene(new AssignmentScene_6());

	#if METRICS
	if (true)
	#else
	if (false)
	#endif
	{

#define MAX_LIGHTS 7

		int scene1SubDivs = 3;

		for (int i = 0; i < scene1SubDivs; i++)
		{
			m_Test.push_back({1, 1 + i, true, true, LIGHTING_ENABLED, MAX_LIGHTS});
		}

		for (int i = 0; i < scene1SubDivs; i++)
		{
			m_Test.push_back({1, 1 + i, true, true, 0, MAX_LIGHTS});
		}

		for (int i = 0; i < scene1SubDivs; i++)
		{
			m_Test.push_back({1, 1 + i, true, false, LIGHTING_ENABLED, MAX_LIGHTS});
		}

		for (int i = 0; i < scene1SubDivs; i++)
		{
			m_Test.push_back({1, 1 + i, false, true, LIGHTING_ENABLED, MAX_LIGHTS});
		}

		for (int i = 0; i < scene1SubDivs; i++)
		{
			m_Test.push_back({1, 1 + i, true, false, 0, MAX_LIGHTS});
		}

		for (int i = 0; i < scene1SubDivs; i++)
		{
			m_Test.push_back({1, 1 + i, false, true, 0, MAX_LIGHTS});
		}

		for (int i = 0; i < MAX_LIGHTS; i++)
		{
			m_Test.push_back({1, 1, true, true, LIGHTING_ENABLED, i});
		}

		int scene2SubDivs = 3;

		for (int i = 0; i < scene2SubDivs; i++)
		{
			m_Test.push_back({2, 1 + i, true, true, LIGHTING_ENABLED, MAX_LIGHTS});
		}

		for (int i = 0; i < scene2SubDivs; i++)
		{
			m_Test.push_back({2, 1 + i, true, true, 0, MAX_LIGHTS});
		}

		for (int i = 0; i < scene2SubDivs; i++)
		{
			m_Test.push_back({2, 1 + i, true, false, LIGHTING_ENABLED, MAX_LIGHTS});
		}

		for (int i = 0; i < scene2SubDivs; i++)
		{
			m_Test.push_back({2, 1 + i, false, true, LIGHTING_ENABLED, MAX_LIGHTS});
		}

		for (int i = 0; i < scene2SubDivs; i++)
		{
			m_Test.push_back({2, 1 + i, true, false, 0, MAX_LIGHTS});
		}

		for (int i = 0; i < scene2SubDivs; i++)
		{
			m_Test.push_back({2, 1 + i, false, true, 0, MAX_LIGHTS});
		}

		for (int i = 0; i < MAX_LIGHTS; i++)
		{
			m_Test.push_back({2, 1, true, true, LIGHTING_ENABLED, i});
		}

		int scene3SubDivs = 3;

		for (int i = 0; i < scene3SubDivs; i++)
		{
			m_Test.push_back({3, 1 + i, true, true, LIGHTING_ENABLED, MAX_LIGHTS});
		}

		for (int i = 0; i < scene3SubDivs; i++)
		{
			m_Test.push_back({3, 1 + i, true, true, LIGHTING_ENABLED | USE_DYNAMIC_DRAW, MAX_LIGHTS});
		}

		int scene4SubDivs = 3;

		for (int i = 0; i < scene4SubDivs; i++)
		{
			m_Test.push_back({4, 1 + i, true, true, LIGHTING_ENABLED, MAX_LIGHTS});
		}

		for (int i = 0; i < scene4SubDivs; i++)
		{
			m_Test.push_back({4, 1 + i, true, true, LIGHTING_ENABLED | USE_DYNAMIC_DRAW, MAX_LIGHTS});
		}

		int scene56SubDivs = 3;

		for (int i = 0; i < scene56SubDivs; i++)
		{
			m_Test.push_back({5, 1 + i, true, true, LIGHTING_ENABLED, MAX_LIGHTS});
		}

		for (int i = 0; i < scene56SubDivs; i++)
		{
			m_Test.push_back({6, 1 + i, true, true, LIGHTING_ENABLED, MAX_LIGHTS});
		}

		SetVsync(false);
		StartTest(0);
	}
	else
	{
		LoadScene(1);
	}

	return 1;
}

void Assignment_1::OnStart()
{
	Application::OnStart();

	m_LastTime = GetCurrentTime();
	m_LastFrame = GetFrameCount();
}

void Assignment_1::UpdateOSD(double avgFPS)
{
	auto add = [this](std::string data) {
		GLTtext* text = gltCreateText();
		gltSetText(text, data.c_str());
		m_Texts.push_back(text);
	};

	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	add("FPS: " + std::to_string(avgFPS));

	if (m_OSDMode)
	{
		add("Scene Name: " + GetScene()->Name());
		auto [w, h] = GetSize();
		add("Display: " + std::to_string(dm.refresh_rate) + "hz " + "width=" + std::to_string(w) + " height=" + std::to_string(h));
		add("Subdivisions: " + std::to_string(g_MengerSponge->m_TotalDepth));
		add("Vertices: " + std::to_string(GetScene()->m_Positions.size()));
		add("Faces: " + std::to_string(GetScene()->m_Indices.size() / 3));
		add("Data: " + std::to_string(SIZE_OF(GetScene()->m_Positions, glm::vec3) + SIZE_OF(GetScene()->m_Normals, glm::vec3) + SIZE_OF(GetScene()->m_Materials, unsigned int)));
		add("Lighting: " + std::string(g_SceneFlags & LIGHTING_ENABLED ? "On" : "Off"));
		add("Depth Testing: " + std::string(m_DepthTesting ? "On" : "Off"));
		add("Backface Culling: " + std::string(m_BackFaceCulling ? "On" : "Off"));
		add("VSync: " + std::string(IsVsync() ? "On" : "Off"));
	}
}

bool Assignment_1::StartTest(int index)
{
	m_TestIndex = index;

	if (m_TestIndex >= m_Test.size())
	{
		RequestExit();
		return false;
	}

	TestState state = m_Test[m_TestIndex];

	LoadScene(state.m_Scene);

	g_MengerSponge->m_TotalDepth = state.m_Subdivision;
	m_BackFaceCulling = state.m_BackFaceCulling;
	m_DepthTesting = state.m_DepthTesting;
	g_NumPointLights = state.m_NumLights;
	g_SceneFlags = state.m_SceneFlags;
	return true;
}

void Assignment_1::UpdateTest(double avgFPS)
{
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	std::cout << GetScene()->Name();
	std::cout << ",";
	std::cout << std::to_string(dm.refresh_rate);
	std::cout << ",";
	std::cout << std::to_string(dm.w);
	std::cout << ",";
	std::cout << std::to_string(dm.h);
	std::cout << ",";
	std::cout << std::to_string(avgFPS);
	std::cout << ",";
	std::cout << std::to_string(g_MengerSponge->m_TotalDepth);
	std::cout << ",";
	std::cout << std::to_string(GetScene()->m_Positions.size());
	std::cout << ",";
	std::cout << std::to_string(GetScene()->m_Indices.size() / 3);
	std::cout << ",";
	std::cout << std::to_string(SIZE_OF(GetScene()->m_Positions, glm::vec3) + SIZE_OF(GetScene()->m_Normals, glm::vec3) + SIZE_OF(GetScene()->m_Materials, unsigned int));
	std::cout << ",";
	std::cout << std::to_string(g_SceneFlags & LIGHTING_ENABLED);
	std::cout << ",";
	std::cout << std::to_string(m_DepthTesting);
	std::cout << ",";
	std::cout << std::to_string(m_BackFaceCulling);
	std::cout << ",";
	std::cout << std::to_string(IsVsync());
	std::cout << std::endl;
}

Uint64 frameDiff;

void Assignment_1::OnTick(double DeltaTime)
{
	Application::OnTick(DeltaTime);

	if (BindingManager::Get("exit") >= BindingState::PRESSED)
	{
		if (BindingManager::IsMouseLocked())
		{
			m_WasMouseLocked = true;
		}

		BindingManager::MouseLock(false);

		if (!m_WasMouseLocked)
		{
			RequestExit();
			return;
		}
	}
	else
		m_WasMouseLocked = false;

	if (BindingManager::Get("scene_1") == BindingState::PRESSED)
	{
		LoadScene(1);
		return;
	}

	if (BindingManager::Get("scene_2") == BindingState::PRESSED)
	{
		LoadScene(2);
		return;
	}

	if (BindingManager::Get("scene_3") == BindingState::PRESSED)
	{
		LoadScene(3);
		return;
	}

	if (BindingManager::Get("scene_4") == BindingState::PRESSED)
	{
		LoadScene(4);
		return;
	}

	if (BindingManager::Get("scene_5") == BindingState::PRESSED)
	{
		LoadScene(5);
		return;
	}

	if (BindingManager::Get("scene_6") == BindingState::PRESSED)
	{
		LoadScene(6);
		return;
	}

	if (BindingManager::Get("focus") >= BindingState::PRESSED)
	{
		if (!BindingManager::IsMouseLocked())
		{
			BindingManager::MouseLock(true);
		}
	}

	if (BindingManager::Get("toggle_facemode") == BindingState::PRESSED)
	{
		m_FaceMode = m_FaceMode == GL_FILL ? GL_LINE : GL_FILL;
	}

	if (BindingManager::Get("toggle_backfaceculling") == BindingState::PRESSED)
	{
		m_BackFaceCulling = !m_BackFaceCulling;
	}

	if (BindingManager::Get("toggle_depthtesting") == BindingState::PRESSED)
	{
		m_DepthTesting = !m_DepthTesting;
	}

	if (BindingManager::Get("toggle_osd") == BindingState::PRESSED)
	{
		m_OSDMode = !m_OSDMode;
	}

	if (BindingManager::Get("toggle_vsync") == BindingState::PRESSED)
	{
		SetVsync(!IsVsync());
	}

	if (BindingManager::Get("toggle_light") == BindingState::PRESSED)
	{
		if (g_SceneFlags & LIGHTING_ENABLED)
		{
			g_SceneFlags &= g_SceneFlags ^ LIGHTING_ENABLED;
		}
		else
		{
			g_SceneFlags |= LIGHTING_ENABLED;
		}
	}

	if (BindingManager::Get("subdiv_increase") == BindingState::PRESSED)
	{
		g_MengerSponge->m_TotalDepth++;
	}

	if (BindingManager::Get("subdiv_decrease") == BindingState::PRESSED)
	{
		g_MengerSponge->m_TotalDepth--;
		if (g_MengerSponge->m_TotalDepth < 1)
			g_MengerSponge->m_TotalDepth = 1;
	}

	if (BindingManager::Get("light_increase") == BindingState::PRESSED)
	{
		g_NumPointLights++;
	}

	if (BindingManager::Get("light_decrease") == BindingState::PRESSED)
	{
		g_NumPointLights--;
	}

	if (g_NumPointLights >= 7)
		g_NumPointLights = 7;
	if (g_NumPointLights < 0)
		g_NumPointLights = 0;

	if (g_MengerSponge->m_PreviousTotalDepth != g_MengerSponge->m_TotalDepth)
	{
		g_MengerSponge->m_PreviousTotalDepth = g_MengerSponge->m_TotalDepth;
		g_MengerSponge->Generate();

		GetScene()->DestroyModel();
		GetScene()->CreateModel();
	}

	GetScene()->OnSimulate(DeltaTime);

	glPolygonMode(GL_FRONT_AND_BACK, m_FaceMode);

	if (m_BackFaceCulling)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	if (m_DepthTesting)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0f);

	auto [width, height] = GetSize();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width, height);

	if (frameDiff >= 100)
	{
		m_LastTime = GetCurrentTime();
		m_LastFrame = GetFrameCount();
	}

	frameDiff = GetFrameCount() - m_LastFrame;
	if (frameDiff >= 100)
	{
		double delta = (double)(GetCurrentTime() - m_LastTime);
		double avgFPS = (frameDiff / delta) * SDL_GetPerformanceFrequency();

		if (m_TestIndex != -1)
		{
			UpdateTest(avgFPS);

			StartTest(m_TestIndex + 1);

			return;
		}

		for (int i = 0; i < m_Texts.size(); i++)
		{
			gltDeleteText(m_Texts[i]);
		}

		m_Texts.clear();

		UpdateOSD(avgFPS);
	}

	if (m_TestIndex != -1)
	{
		if (m_TestIndex >= m_Test.size()) return;
	}
	else
	{
		gltBeginDraw();
		for (int i = 0; i < m_Texts.size(); i++)
		{
			gltColor(1.0f, 1.0f, 1.0f, 1.0f);
			gltDrawText2D(m_Texts[i], 5.f, 5.f + (i * 20.f), 1.f);
		}
		gltEndDraw();
	}

	GetScene()->SetProjectionTransform(glm::perspective(90.0f, (GLfloat)width / (GLfloat)height, 0.001f, 100.0f));

	g_DirectionalLight.direction = -glm::inverse(GetScene()->GetViewTransform())[2];

	GetScene()->OnRender(DeltaTime);
}

void Assignment_1::AddScene(Ref<Scene> scene)
{
	m_Scenes.push_back(scene);
}

void Assignment_1::LoadScene(int num)
{
	g_MengerSponge->m_PreviousTotalDepth = g_MengerSponge->m_TotalDepth;
	SetScene(m_Scenes[(int)(num - 1)]);
}

int main(int argc, char** argv)
{
	Assignment_1* app = new Assignment_1("Assignment 1", true, 500, 500);
	app->Start();
	return 0;
}
