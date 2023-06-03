//--------------------------------------------------
// Ants
// worldComponent.cpp
// Date: 2022-08-20
// By Breno Cunha Queiroz
//--------------------------------------------------
#include "worldComponent.h"

//#ifndef __NVCC__
//template <>
//cmp::ComponentDescription& cmp::TypedRegistry<WorldComponent>::getDescription() {
//    static cmp::ComponentDescription desc = {
//        "World",
//        {
//            {AttributeType::FLOAT32, offsetof(WorldComponent, evaporate), "evaporate"},
//            {AttributeType::FLOAT32, offsetof(WorldComponent, blur), "blur"},
//            {AttributeType::CUSTOM, offsetof(WorldComponent, pheromones), "pheromones"},
//        },
//        // Max instances
//        1,
//        // Serialize (do not serialize pheromone)
//        {{"pheromones", [](std::ostream& os, void* data) {}}},
//        // Deserialize (do not deserialize pheromone)
//        {{"pheromones", [](std::istream& is, void* data) {}}},
//    };
//
//    return desc;
//}
//#endif
