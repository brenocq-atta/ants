//--------------------------------------------------
// Ants
// worldComponent.h
// Date: 2022-08-20
// By Breno Cunha Queiroz
//--------------------------------------------------
#ifndef WORLD_COMPONENT_H
#define WORLD_COMPONENT_H
#include <atta/component/interface.h>

namespace cmp = atta::component;

struct WorldComponent final : public cmp::Component {
    float evaporate;///< Seconds between evaporate runs
    float blur;///< Seconds between blur runs
    static constexpr uint8_t numPheromones = 3;
    static constexpr uint8_t width = 100;
    static constexpr uint8_t height = 100;
    uint8_t pheromones[numPheromones][width*height];///< Three types of pheromone
};
ATTA_REGISTER_COMPONENT(WorldComponent);
template <>
cmp::ComponentDescription& cmp::TypedComponentRegistry<WorldComponent>::getDescription();

#endif // WORLD_COMPONENT_H
