#pragma once

#ifdef PHSX_PLATFORM_WINDOWS
#include "Application.h"
#include <stdio.h>

extern Physx2D::Application* Physx2D::CreateApplication();

int main(int argc, char** argv) {
	auto app = Physx2D::CreateApplication();
	
	printf("Application successfully created !!!");
	app->Run();
	delete app;
}

#endif
