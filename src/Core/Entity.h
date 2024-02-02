#pragma once

#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <queue>

namespace sim3D {

using Entity = std::uint32_t;
const std::uint32_t kMaxEntities = 5000;
using ComponentType = std::uint8_t;
const std::uint32_t kMaxComponents = 32;
using Signature = std::bitset<kMaxComponents>;


struct Transform {
  glm::vec3 position;
  glm::vec3 scale;
  glm::quat rotation;
};

class EntityManager {
public:
  EntityManager() {
    // Initialize the queue with all possible entity IDs
    for (Entity entity = 0; entity < kMaxEntities; ++entity) {
      m_available_entities.push(entity);
    }
  }

  auto CreateEntity() -> Entity {
    assert(m_living_entity_count < kMaxEntities && "Too many entities in existance.");

    // Take an ID from the front of the queue
    Entity id = m_available_entities.front();
    m_available_entities.pop();
    ++m_living_entity_count;

    return id;
  }

  auto DestroyEntity(Entity entity) -> void {
    assert(entity < kMaxEntities && "Entity out of range.");
    //Invalidate the destory entity's Signature
    m_signatures[entity].reset();

    // Put the destroyed ID at the back of the queue
    m_available_entities.push(entity);
    --m_living_entity_count;
  }

  auto SetSignature(Entity entity, Signature signature) -> void {
    assert(entity < kMaxEntities && "Entity out of range.");
    // Put this entity's signature into the array
    m_signatures[entity] = signature;
  }

  auto GetSignature(Entity entity) {
    assert(entity < kMaxEntities && "Entity out of range.");

    // Get this entity's signature from the array
    return m_signatures[entity];
  }

private:

  // queue of unused entity IDs
  std::queue<Entity> m_available_entities{};
  // Array of signatures where the index corresponds to the entity ID
  std::array<Signature, kMaxEntities> m_signatures{};
  // Total living entities
  std::uint32_t m_living_entity_count{};
};

}
