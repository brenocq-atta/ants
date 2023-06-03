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
    for (auto& f : _world.get<WorldComponent>()->pheromones)
        for (int i = 0; i < w * h; i++)
            f[i] = 0;
}

ATTA_CPU_GPU void World::onUpdateBefore() {
    _world = cmp::Entity(0);
    _antPrototype = cmp::Entity(1);
    uint32_t w = WorldComponent::width;
    uint32_t h = WorldComponent::height;
    auto& pheromones = _world.get<WorldComponent>()->pheromones;
    float dt = 0.015;

    _lastBlur += dt;
    _lastEvaporate += dt;

    // Blur
    {
        if (_lastBlur >= _world.get<WorldComponent>()->blur) {
            _lastBlur = 0;
            for (int f = 0; f < WorldComponent::numPheromones; f++)
                for (int y = 1; y < h - 1; y++) {
                    for (int x = 1; x < w - 1; x++) {
                        int sum = 0;
                        for (int yn = y - 1; yn <= y + 1; yn++)
                            for (int xn = x - 1; xn <= x + 1; xn++)
                                sum += pheromones[f][yn * w + xn];
                        int old = pheromones[f][y * w + x];
                        pheromones[f][y * w + x] = old * 0.9f + (sum / 9.0f) * 0.1f;
                    }
                }
        }
    }

    // Evaporate
    {
        if (_lastEvaporate >= _world.get<WorldComponent>()->evaporate) {
            _lastEvaporate = 0;
            for (int f = 0; f < WorldComponent::numPheromones; f++)
                for (int i = 0; i < w * h; i++)
                    pheromones[f][i] = std::max(int(pheromones[f][i]) - 1, 0);
        }
    }

    // Update pheromone
    uint32_t num = _antPrototype.get<cmp::Prototype>()->maxClones;
    for (cmp::EntityId i = 2; i < 2 + num; i++) {
        AntComponent* a = cmp::Entity(i).get<AntComponent>();
        int x = int(a->position.x);
        int y = int(a->position.y);
        if (x >= 0 && y >= 0 && x < w && y < h)
            pheromones[0][y * w + x] = 255;
    }
}

ATTA_CPU_GPU void World::onUpdateAfter() {}
