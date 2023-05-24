#include "pch.h"
#include "Application.h"


namespace Physx2D {
	Application::Application() {
		LOG_INFO("Application Creation Started%s", "\n");
		m_window = std::unique_ptr<Window>(new Window());
		m_window->OnInit();
	}

	Application::~Application() {
		LOG_INFO("Application Successfully Destroyed%s", "\n");
	}
	void Application::Run()
	{
	}
}