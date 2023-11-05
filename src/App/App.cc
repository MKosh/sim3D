#include "App.h"

auto App::TogglePhysics() -> void {
  m_physics_active = m_physics_active ? false : true;
}

