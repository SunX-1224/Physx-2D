#include "physx2d.h"

class SandBox :public Physx2D::Application {

public:
	SandBox() {

	}
	~SandBox() {

	}
};


Physx2D::Application* Physx2D::CreateApplication() {
	return new SandBox();
}
