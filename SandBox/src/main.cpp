#include "../applications/boid_sim.h"
#include "../applications/cellularAutomata.h"
#include "../applications/MNCA.h"
#include "../applications/WaveFuncCollapseApp.h"
#include "../applications/PhysicsTestApp.h"

#include "core/entry.h"

Physx2D::Application* Physx2D::CreateApplication() {
	return new PhysicsTestApp(200);
}
