//--------------------------------------------------
// Ants
// world.cpp
// Date: 2022-08-20
// By Breno Cunha Queiroz
//--------------------------------------------------
#include "world.h"
#include "antComponent.h"
#include "worldComponent.h"
#include <atta/component/components/prototype.h>

ATTA_CPU_GPU void World::onStart() {
    // srand(42); // Repeatable simulations
    _world = cmp::Entity(0);
    _world.get<WorldComponent>()->time = 0;

    _antPrototype = cmp::Entity(1);
    uint32_t num = _antPrototype.get<cmp::Prototype>()->maxClones;

    // Init ants
    for (cmp::EntityId i = 2; i < 2 + num; i++) {
        AntComponent* a = cmp::Entity(i).get<AntComponent>();
        float r = (i - 2) / float(num + 1);
        a->position = atta::vec2(int(r * 154) % 100, int(r * 353) % 100);
        a->angle = r * M_PI * 2;
    }
}

ATTA_CPU_GPU void World::onStop() {
    _world = cmp::Entity(0);
    uint32_t w = WorldComponent::width;
    uint32_t h = WorldComponent::height;
    auto& pheromones = _world.get<WorldComponent>()->pheromones;
    auto& antOnTop = _world.get<WorldComponent>()->antOnTop;
    for (int i = 0; i < w * h; i++) {
        pheromones[i] = 0;
        antOnTop[i] = 0;
    }
}

ATTA_CPU_GPU void World::onUpdateBefore() {
    _world = cmp::Entity(0);
    WorldComponent* worldComp = _world.get<WorldComponent>();

    auto& pheromones = _world.get<WorldComponent>()->pheromones;
    auto& antOnTop = _world.get<WorldComponent>()->antOnTop;

    // Update pheromones
    {
        uint32_t time = worldComp->time;
        uint32_t w = WorldComponent::width;
        uint32_t h = WorldComponent::height;
        for (int i = 0; i < w * h; i++) {
            if (antOnTop[i]) {
                antOnTop[i] = 0;
                pheromones[i] = time;
            }
        }
    }

    // Increase step
    worldComp->time++;
}

ATTA_CPU_GPU void World::onUpdateAfter() {}
