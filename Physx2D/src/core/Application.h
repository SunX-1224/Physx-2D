#pragma once

#include "core.h"

namespace Physx2D {
	class PHYSX2D_API Application {
	public:
		Application();

		~Application();

		void Run() {
			while (1);
		}
	};

	Application* CreateApplication();
}
