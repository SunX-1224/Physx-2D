#pragma once
#include "pch.h"
#include "../window/window.h"
#include "ecsmanager.h"
#include "../physics/physics2d.h"
#include "../renderer/texture.h"
#include "../renderer/instancedRenderer.h"
#include "../utils/quadtree.h"
#include "camera.h"

namespace Physx2D {

	class PHYSX2D_API Entity;

	class PHYSX2D_API World {
		public:

			Camera sceneCamera;

			World(Window* targetWindow);
			~World();

			void Initialize();
			void Update(double delta_time);
			void Render();

			Entity* CreateEntity(std::string name = std::string());

			inline void loadShader(const char* vertexPath, const char* fragPath, uint32_t ID);
			inline void loadTexture(const char* path, const char* type, uint32_t ID, uint32_t slot = 0);

			InstancedRenderer* addInstancedRenderer(uint32_t type, std::vector<float> vertices, uint32_t numPoints, GLenum draw_mode);
			InstancedRenderer* addInstancedRenderer(uint32_t type, std::vector<float> vertices, std::vector<uint32_t> indices, GLenum draw_mode);

		private:
			Window* window = nullptr;

			ECSManager manager;
			std::vector<Entity*> entities;
			std::unordered_map<uint32_t, std::shared_ptr<Shader>> shaders;
			std::unordered_map<uint32_t, std::shared_ptr<Texture>> textures;

			std::unordered_map<uint32_t, InstancedRenderer> renderers;

			std::unordered_map<uint32_t, std::vector<RenderData>> renderData;
			
			void handleScriptUpdate(float delta_time);
			void handlePhysics(double delta_time);
			void handleCollisions();
			void updateRenderData();
			
			friend class Entity;
	};
}