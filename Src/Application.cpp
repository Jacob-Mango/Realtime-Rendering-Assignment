#define STB_IMAGE_IMPLEMENTATION

#include "Application.h"

#include "Binding.h"
#include "Scene.h"

Application::Application(std::string title, bool fullscreen, int width, int height) : m_Title(title), m_Fullscreen(fullscreen), m_WindowWidth(width), m_WindowHeight(height)
{
}

Application::~Application()
{
	SDL_GL_DeleteContext(m_GLContext);
	SDL_DestroyRenderer(m_SDLRenderer);
	SDL_DestroyWindow(m_SDLWindow);
	SDL_Quit();
}

int Application::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_CaptureMouse(SDL_TRUE);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	int windowsFlags = SDL_WINDOW_OPENGL;
	int posFlag = SDL_WINDOWPOS_CENTERED;
	if (m_Fullscreen)
	{
		windowsFlags |= SDL_WINDOW_FULLSCREEN;
		posFlag = SDL_WINDOWPOS_UNDEFINED;
		m_WindowWidth = 0;
		m_WindowHeight = 0;
	}

	m_SDLWindow = SDL_CreateWindow(m_Title.c_str(), posFlag, posFlag, m_WindowWidth, m_WindowHeight, windowsFlags);
	if (m_SDLWindow == nullptr)
	{
		std::cerr << "RTR:ERROR: Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	m_SDLRenderer = SDL_CreateRenderer(m_SDLWindow, -1, SDL_RENDERER_ACCELERATED);
	if (m_SDLRenderer == nullptr)
	{
		std::cerr << "RTR:ERROR: SDL2 Renderer couldn't be created. Error: " << SDL_GetError() << std::endl;
		return false;
	}

	m_GLContext = SDL_GL_CreateContext(m_SDLWindow);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cerr << "RTR:ERROR: Failed to initialize the OpenGL context." << std::endl;
		return false;
	}

	SDL_DisplayMode dm;
	if (SDL_GetCurrentDisplayMode(0, &dm) != 0)
	{
		std::cerr << "RTR:ERROR: SDL coudn't retrieve current display mode details. SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	m_ScreenWidth = dm.w;
	m_ScreenHeight = dm.h;

	if (m_Fullscreen)
	{
		m_WindowWidth = m_ScreenWidth;
		m_WindowHeight = m_ScreenHeight;
	}

	//std::cout << "RTR:MESSAGE: OpenGL version " << GLVersion.major << "." << GLVersion.minor << " initialised." << std::endl;

	BindingManager::Init(this);

	return true;
}

void Application::Start()
{
	if (m_IsRunning)
	{
		std::cout << "Failed to start Application, already running." << std::endl;
		return;
	}

	if (Init() != 1)
	{
		std::cout << "Failed to start Application, initialize failed." << std::endl;
		return;
	}

	m_IsRunning = true;

	if (m_Scene != nullptr)
	{
		m_Scene->OnStart();
	}

	m_CurrentTime = SDL_GetPerformanceCounter();

	double frameTime = 0;
	Uint64 frames = 0;

	OnStart();

	while (m_IsRunning)
	{
		Uint64 previousTime = m_CurrentTime;
		m_CurrentTime = SDL_GetPerformanceCounter();
		m_DeltaTime = (double)(m_CurrentTime - previousTime) / (double)SDL_GetPerformanceFrequency();

		frameTime += m_DeltaTime;
		frames++;
		m_FrameCounter++;
		if (frameTime >= 1)
		{
			m_FPS = frames;
			frameTime = 0;
			frames = 0;
		}

		BindingManager::Update();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			HandleEvents(event);
		}

		OnTick((float)m_DeltaTime);

		SDL_GL_SwapWindow(m_SDLWindow);
	}

	if (m_IsRunning)
	{
		Stop();
	}
}

void Application::Stop()
{
	if (!m_IsRunning)
	{
		std::cout << "Failed to stop Application, already stopped." << std::endl;
		return;
	}

	m_IsRunning = false;
	m_RequestingExit = false;

	OnStop();

	if (m_Scene != nullptr)
	{
		m_Scene->OnStop();
	}
}

void Application::RequestExit()
{
	m_RequestingExit = true;
}

void Application::ClearExitRequest()
{
	m_RequestingExit = false;
}

bool Application::RequestingExit()
{
	return m_RequestingExit;
}

bool Application::IsVsync() const
{
	return m_Vsync;
}

void Application::SetVsync(bool enabled)
{
	m_Vsync = enabled;

	SDL_GL_SetSwapInterval(m_Vsync);
}

std::pair<int, int> Application::GetSize()
{
	return {m_WindowWidth, m_WindowHeight};
}

SDL_Window* Application::GetWindow()
{
	return m_SDLWindow;
}

Uint64 Application::GetFrameCount() const
{
	return m_FrameCounter;
}

Uint64 Application::GetFPS() const
{
	return m_FPS;
}

Uint64 Application::GetCurrentTime() const
{
	return m_CurrentTime;
}

void Application::HandleEvents(SDL_Event& event)
{
	BindingManager::OnEvent(event);

	switch (event.type)
	{
	case SDL_QUIT:
		RequestExit();
		break;
	}
}

void Application::OnStart()
{
}

void Application::OnStop()
{
}

void Application::OnTick(double DeltaTime)
{
	if (RequestingExit())
		Stop();
}

void Application::SetScene(Ref<Scene> Scene)
{
	if (m_IsRunning && m_Scene != nullptr)
	{
		m_Scene->OnStop();
	}

	m_Scene = Scene;

	if (m_IsRunning && m_Scene != nullptr)
	{
		m_Scene->OnStart();
	}
}

Ref<Scene> Application::GetScene() const
{
	return m_Scene;
}