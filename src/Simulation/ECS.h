#include <bitset>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>


namespace sim3D {

const std::uint32_t kMaxComponents = 32;
const std::uint32_t kMaxEntities = 5000;
using EntityID = std::uint64_t;
using ComponentMask = std::bitset<kMaxComponents>;
extern int s_component_counter;

// struct Transform {
//   glm::vec3 position;
//   glm::vec3 scale;
//   glm::vec3 axis;
//   glm::mat4 rotation;
// };

struct Transform {
  glm::mat4 transform{1};
};

struct Momentum {
  glm::vec3 momentum;
};

struct Mass {
  float mass;
};

struct ComponentPool {
  ComponentPool(std::size_t element_size) {
    m_element_size = element_size;
    m_data = new char[m_element_size * kMaxEntities];
  }

  ~ComponentPool() {
    delete[] m_data;
  }

  // ComponentPool& operator=(const ComponentPool& RHS) {
  //
  // }

  inline auto get(std::size_t index) -> void* {
    return m_data + index * m_element_size;
  }

  char* m_data{nullptr};
  std::size_t m_element_size{0};
};

struct Scene {
  struct EntityDesc {
    EntityID id;
    ComponentMask mask;
  };

  std::vector<EntityDesc> entities;
  std::vector<ComponentPool> component_pools;

  auto NewEntity() -> EntityID {
    entities.push_back({entities.size(), ComponentMask()});
    return entities.back().id;
  }

  template<typename T>
  auto Assign(EntityID id) -> T* {
    int componentID = GetID<T>();

    if (component_pools.size() <= componentID) {// Not enough component pool
      component_pools.emplace_back(ComponentPool(sizeof(T)));
      // component_pools.resize(componentID + 1, 0);
    }

    // if (component_pools.size() == componentID+1) { // Possibly problematic different from the website (component_pools[componentID] == nullptr)
    //   // component_pools[componentID] = new ComponentPool(sizeof(T));
    //   component_pools.push_back(ComponentPool(sizeof(T)));
    // }

    T* component = new (component_pools[componentID].get(id)) T();

    entities[id].mask.set(componentID);
    return component;
  }

  template<typename T>
  auto Get(EntityID id) -> T* {
    int componentID = GetID<T>();
    if (!entities[id].mask.test(componentID)) {
      return nullptr;
    }

    T* component = static_cast<T*>(component_pools[componentID].get(id));
    return component;
  }

  template<typename T>
  auto Unassign(EntityID id) -> void {
    int componentID = GetID<T>();
    entities[id].mask.reset(componentID);
  }
};

template<typename T>
auto GetID() -> int {
  static int s_componentID = s_component_counter++;
  return s_componentID;
}

auto DrawScene(const Scene& scene) -> void {

  for (const auto& entity : scene.entities) {
    
  }
}

}
