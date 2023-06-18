#pragma once

/*
	ECSManager is manager unit for Entity Component System of the engine.

	> Every entity has EntityID which is just an uint32_t
	> Data oriented approach is taken to reduce the problem of inheritance
*/

#include "../pch.h"

namespace Physx2D {
	using EntityID = uint32_t;

	class PHYSX2D_API ECSManager {

	public:

		const inline EntityID  CreateEntity() {
			return nextEntity++;
		}

		template<typename T>
		T* addComponent(EntityID entity, T* component) {
			PHSX_ASSERT(entity >= 0 && entity < nextEntity, "Invalid entity ID : %d", entity);

			std::vector<void*>& componentVector = componentStorage[std::type_index(typeid(T))];
			if (entity >= componentVector.size()) {
				componentVector.resize(entity + 16, nullptr);
			}

			if (componentVector[entity] != nullptr) 
				delete ((T*)componentVector[entity]);

			componentVector[entity] = component;
			return static_cast<T*>(componentVector[entity]);
		}

		template<typename T>
		void removeComponent(EntityID entity) {
			PHSX_ASSERT(entity >= 0 && entity < nextEntity, "Invalid entity ID : %d", entity);

			std::vector<void*>& componentVector = componentStorage[std::type_index(typeid(T))];
			delete ((T*)componentVector[entity]);
		}

		template<typename T>
		inline bool hasComponent(EntityID entity) {
			PHSX_ASSERT(entity >= 0 && entity < nextEntity, "Invalid entity ID : %d", entity);

			std::vector<void*>& componentVector = componentStorage[std::type_index(typeid(T))];
			return entity < componentVector.size() && componentVector[entity] ;
		}

		template<typename T>
		T* getComponent(EntityID entity) {
			PHSX_ASSERT(entity >= 0 && entity < nextEntity, "Invalid entity ID : %d", entity);

			std::vector<void*>& componentVector = componentStorage[std::type_index(typeid(T))];

			if (entity < componentVector.size()) {
				return static_cast<T*>(componentVector[entity]);
			}
			return nullptr;
		}

		template<typename T>
		const inline std::vector<void*>& getAllComponents() {
			return componentStorage[std::type_index(typeid(T))];
		}

		~ECSManager() {
			componentStorage.clear();
		}

	private:
		EntityID nextEntity = 0;
		
		std::unordered_map<std::type_index, std::vector<void*>> componentStorage;

	};
}