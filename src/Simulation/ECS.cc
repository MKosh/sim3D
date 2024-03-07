#include "ECS.h"

namespace sim3D {

auto Scene::NewEntity() -> EntityID {
  entities.push_back({entities.size(), ComponentMask()});
  return entities.back().id;
}


}
