#pragma once
#include "pch.h"
#include "../window/window.h"

namespace Physx2D {
	class PHYSX2D_API Application {
	public:
		Application();

		~Application();

		virtual void Run();

	protected:
		std::unique_ptr<Window> m_window;
	};

	Application* CreateApplication();


}
