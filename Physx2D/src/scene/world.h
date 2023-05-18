#pragma once

#include "../core/core.h"

#include "../window/window.h"
#include "ecsmanager.h"
#include "../utils/defaults.h"
#include "../physics/physics2d.h"
#include "../renderer/shader.h"
#include "../renderer/instancedRenderer.h"
#include "../utils/quadtree.h"

namespace Physx2D {

	class PHYSX2D_API Entity;

	class PHYSX2D_API World {
		public:

			World(Window* targetWindow);
			~World();

			void Initialize();
			void Update(double delta_time);
			void Render();

			Entity* CreateEntity(std::string name = std::string());

			void loadShader(const char* vertexPath, const char* fragPath, uint32_t ID);

			InstancedRenderer* addInstancedRenderer(uint32_t type, std::vector<vec2> vertices, GLenum draw_mode);
			InstancedRenderer* addInstancedRenderer(uint32_t type, std::vector<vec2> vertices, std::vector<uint32_t> indices, GLenum draw_mode);

		private:
			Window* window = nullptr;

			ECSManager manager;
			std::vector<Entity*> entities;
			std::unordered_map<uint32_t, std::shared_ptr<Shader>> shaders;

			std::unordered_map<uint32_t, InstancedRenderer> renderers;

			std::unordered_map<uint32_t, std::vector<RenderData>> renderData;
			
			void handleScriptUpdate();
			void handlePhysics(double delta_time);
			void handleCollisions();
			void updateRenderData();
			
			friend class Entity;
	};
}