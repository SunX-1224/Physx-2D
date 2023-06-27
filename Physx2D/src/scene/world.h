#pragma once

/*
	World is a global event handler for engine. It keeps track of all the entities, physics, collision, rendering, scripts, etc.
	Plus it tracks all the shaders and textures of the application..
*/

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

			World(const Window* targetWindow);
			virtual ~World();

			void loadDefaultRenderer(RenderType type = DEFAULT);

			void Update(double delta_time);
			void Render();

			Entity* CreateEntity(const char* name = "Entity");

			inline void loadShader(const char* vertexPath, const char* fragPath, uint32_t ID = DEFAULT, bool is_path = true);
			inline void loadTexture(const char* path, const char* type, uint32_t ID, int slot = -1);

			InstancedRenderer* addInstancedRenderer(uint32_t type, std::vector<float> vertices, uint32_t numPoints, GLenum draw_mode);
			InstancedRenderer* addInstancedRenderer(uint32_t type, std::vector<float> vertices, std::vector<uint32_t> indices, GLenum draw_mode);

		private:
			const Window* window;

			ECSManager* manager;
			std::vector<Entity*> entities;
			
			std::unordered_map<uint32_t, Shader*> shaders;
			std::unordered_map<uint32_t, std::vector<Texture*>> textures;

			std::unordered_map<uint32_t, InstancedRenderer*> renderers;

			std::unordered_map<uint32_t, std::vector<RenderData>> renderData;
			
			void handleScripts(float delta_time);
			void handlePhysics(double delta_time);
			void handleCollisions();
			void updateRenderData();
			void setDefaultLayout(uint32_t type);
			
			friend class Entity;
	};
}