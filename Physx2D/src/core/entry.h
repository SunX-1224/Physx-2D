#pragma once
/*
	This is the entry point for the whole application. CreateApplication function which is
	defined externally returns the application which is got by the main function and runs it.
*/

#include "Application.h"

extern Physx2D::Application* Physx2D::CreateApplication();

int main(int argc, char** argv) {
	auto app = Physx2D::CreateApplication();
	
	app->Run();

	delete app;
}

