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
    atta::random::seed();

    _world = cmp::Entity(0);
    _world.get<WorldComponent>()->time = 0;

    _antPrototype = cmp::Entity(1);
    uint32_t num = _antPrototype.get<cmp::Prototype>()->maxClones;

    // Init ants
    for (cmp::EntityId i = 2; i < 2 + num; i++) {
        AntComponent* a = cmp::Entity(i).get<AntComponent>();
        a->position = atta::vec2(atta::random::uniform(0.0f, 100.0f), atta::random::uniform(0.0f, 100.0f));
        a->angle = atta::random::uniform(0.0f, 2 * M_PI);
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
