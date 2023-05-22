#pragma once
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
			if(entity < 0 || entity >= nextEntity) throw("Invalid entity ID");

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
			if (entity < 0 || entity >= nextEntity) throw("Invalid entity ID");

			std::vector<void*>& componentVector = componentStorage[std::type_index(typeid(T))];
			delete ((T*)componentVector[entity]);
		}

		template<typename T>
		inline bool hasComponent(EntityID entity) {
			if (entity < 0 || entity >= nextEntity) throw("Invalid entity ID");

			std::vector<void*>& componentVector = componentStorage[std::type_index(typeid(T))];
			return entity < componentVector.size() && componentVector[entity] ;
		}

		template<typename T>
		T* getComponent(EntityID entity) {
			if (entity < 0 || entity >= nextEntity) throw("Invalid entity ID");

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