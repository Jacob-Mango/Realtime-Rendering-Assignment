#pragma once

#include <glad/glad.h>
#include <gltext/gltext.h>
#include <iostream>
#include <sdl/SDL.h>
#include <stb/stb_image.h>
#include <string>

#include "Reference.h"

class Scene;

class Application : public Countable
{
private:
	bool m_IsRunning = false;
	bool m_RequestingExit = false;

	std::string m_Title;
	bool m_Fullscreen;
	int m_ScreenWidth;
	int m_ScreenHeight;
	int m_WindowWidth;
	int m_WindowHeight;

	bool m_Vsync;

	Uint64 m_CurrentTime = 0;
	Uint64 m_FPS = 0;
	double m_DeltaTime = 0;

	Uint64 m_FrameCounter = 0;

	Ref<Scene> m_Scene;

protected:
	SDL_Window* m_SDLWindow = nullptr;
	SDL_Renderer* m_SDLRenderer = nullptr;
	SDL_GLContext m_GLContext = nullptr;

public:
	Application(std::string title, bool fullscreen, int width, int height);
	virtual ~Application();

	virtual int Init();

	void Start();
	void Stop();

	void RequestExit();
	void ClearExitRequest();
	bool RequestingExit();

	bool IsVsync() const;
	void SetVsync(bool enabled);

	Uint64 GetFrameCount() const;
	Uint64 GetFPS() const;
	Uint64 GetCurrentTime() const;

	std::pair<int, int> GetSize();
	SDL_Window* GetWindow();

	void HandleEvents(SDL_Event& event);

	virtual void OnStart();
	virtual void OnStop();
	virtual void OnTick(double DeltaTime);

	void SetScene(Ref<Scene> Scene);
	Ref<Scene> GetScene() const;
};
