#include "Application.h"

extern Physx2D::Application* Physx2D::CreateApplication();

int main(int argc, char** argv) {
	auto app = Physx2D::CreateApplication();
	
	app->Run();

	delete app;
}

