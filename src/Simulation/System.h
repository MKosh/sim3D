#include <memory>
#include <unordered_map>
namespace sim3D {

class SystemManager {
public:
  template<typename T>
  auto RegisterSystem() -> std::shared_ptr<T>{
    const char* type_name = typeid(T).name();

    // assert(m_systems.find(type_name) == m_systems.end() && "Registering system more than once.");

    auto system = std::make_shared<T>();
    // m_systems.insert({type_name, system});
    return system;
  }

private:
  // Map from system type string pointer to a signature
  // std::unordered_map<const char*, Signature> m_signatures{};

  // Map from system type string pointer to a system pointer
  // std::unordered_map<const char*, std::shared_ptr<System>> m_systems{};
  
};

}
