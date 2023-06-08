//--------------------------------------------------
// Ants
// worldComponent.h
// Date: 2022-08-20
// By Breno Cunha Queiroz
//--------------------------------------------------
#ifndef ANTS_WORLD_COMPONENT_H
#define ANTS_WORLD_COMPONENT_H
#include <atta/component/components/component.h>

struct WorldComponent final : public atta::component::Component {
    static constexpr float evaporate = 10; ///< How many steps it takes to evaporate one unit
    static constexpr uint8_t width = 100;
    static constexpr uint8_t height = 100;
    uint32_t time;                       ///< Current time
    uint8_t antOnTop[width * height];    ///< Three types of pheromone
    uint32_t pheromones[width * height]; ///< Three types of pheromone
};

#ifndef __NVCC__
#include <atta/component/registry/typedRegistry.h>
ATTA_REGISTER_COMPONENT(WorldComponent);
// template <>
// cmp::ComponentDescription& cmp::TypedRegistry<WorldComponent>::getDescription();
#endif

#endif // ANTS_WORLD_COMPONENT_H
