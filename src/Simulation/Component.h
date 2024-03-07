#pragma once

#include "Entity.h"
#include <cassert>
#include <cstddef>
#include <memory>
#include <unordered_map>
#include <typeinfo>

namespace sim3D {

class IComponentArray {
public:
  virtual ~IComponentArray() = default;
  virtual auto EntityDestroyed(Entity entity) -> void = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
public:
  auto InsertData(Entity entity, T component) -> void {
    assert(m_entity_to_index.find(entity) == m_entity_to_index.end() && "Component added to same entity more than once");
    
    // Put the new entry at the end and update the maps
    size_t new_index = m_size;
    m_entity_to_index[entity] = new_index;
    m_index_to_entity[new_index] = entity;
    m_components[new_index] = component;
    ++m_size;
  }

  auto RemoveData(Entity entity) -> void {
    assert(m_entity_to_index.find(entity) != m_entity_to_index.end() && "Removing non-existent component");

    // Copy element at end into deleted element's place
    size_t removed_entity_index = m_entity_to_index[entity];
    size_t last_element_index = m_size - 1;
    m_components[removed_entity_index] = m_components[last_element_index];

    // Update map to point to moved spot
    Entity last_element_id = m_index_to_entity[last_element_index];
    m_entity_to_index[last_element_id] = removed_entity_index;
    m_index_to_entity[removed_entity_index] = last_element_id;

    m_entity_to_index.erase(entity);
    m_index_to_entity.erase(last_element_index);

    --m_size;
  }

  auto GetData(Entity entity) -> T& {
    assert(m_entity_to_index.find(entity) != m_entity_to_index.end() && "Retrieving non-existent component.");
    
    // Return a reference to the entity's component
    return m_components[m_entity_to_index[entity]];
  }

  auto EntityDestroyed(Entity entity) -> void {
    if (m_entity_to_index.find(entity) != m_entity_to_index.end()) {
      RemoveData(entity);
    }
  }

private:
  // The packed array of components
  std::array<T, kMaxEntities> m_components;

  // Map from the entity ID to an index in the array
  std::unordered_map<Entity, size_t> m_entity_to_index;

  // Map from an index in the array to an entity ID
  std::unordered_map<size_t, Entity> m_index_to_entity;

  // Total size of valid entiries in the array
  size_t m_size;
};

class ComponentManager {
public:
  template<typename T>
  auto RegisterComponent() -> void {
    const char* type_name = typeid(T).name();

    assert(m_component_types.find(type_name) == m_component_types.end() && "Registering component type more than once.");

    // Add this component type to the component type map
    m_component_types.insert({type_name, m_next_component_type});

    // Create a component array pointer and add it to the component arrays map
    m_components.insert({type_name, std::make_shared<ComponentArray<T>>()});

    // Increment the value so thta the next component registered will be different
    ++m_next_component_type;

  }

  template<typename T>
  auto GetComponentType() -> ComponentType {
    const char* type_name = typeid(T).name();

    assert(m_component_types.find(type_name) != m_component_types.end() && "Component not registered before use.");

    // Return this component's type - used for creating signatures
    return m_component_types[type_name];
  }

private:

  // Map from type string pointer to a component type
  std::unordered_map<const char*, ComponentType> m_component_types{};

  // Map from type string pointer to a component array
  std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_components{};

  // The component type to be assigned to the next registered component starting at 0
  ComponentType m_next_component_type{};

  // Convenience function to get the statically casted pointer to the component array of type T
  template<typename T>
  auto GetComponentArray() -> std::shared_ptr<ComponentArray<T>> {
    const char* type_name = typeid(T).name();

    assert(m_component_types.find(type_name) != m_component_types.end() && "Component not registered before use.");

    return std::static_pointer_cast<ComponentArray<T>>(m_components[type_name]);
  }
};

}
