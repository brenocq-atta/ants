//--------------------------------------------------
// Ants
// ant.cpp
// Date: 2023-05-25
// By Breno Cunha Queiroz
//--------------------------------------------------
#include "ant.h"
#include "antComponent.h"
#include "worldComponent.h"

ATTA_CPU_GPU void Ant::update() {
    _world = cmp::Entity(0);

    AntComponent* ant = get<AntComponent>();

    float a1 = ant->angle + M_PI / 3;
    float a2 = ant->angle - M_PI / 3;
    float r = 5.0f;

    // Sense pheromone
    uint16_t s1 = sense(ant->position + atta::vec2(cos(a1), sin(a1)) * r);
    uint16_t s2 = sense(ant->position + atta::vec2(cos(a2), sin(a2)) * r);

    // Change angle
    if (s1 + s2 != 0) {
        ant->angle = ant->angle * 0.5f + ((a1 * s1 + a2 * s2) / (s1 + s2)) * 0.5f;
        ant->angle += atta::random::uniform(-0.01f, 0.01f);
    }

    // Wrap angle
    while (ant->angle > M_PI * 2)
        ant->angle -= M_PI * 2;
    while (ant->angle < 0)
        ant->angle += M_PI * 2;

    // Change position
    ant->position.x += (cos(ant->angle)) * 0.01;
    ant->position.y += (sin(ant->angle)) * 0.01;

    // Wrap around
    uint32_t w = WorldComponent::width;
    uint32_t h = WorldComponent::height;
    if (ant->position.x > w)
        ant->position.x -= w;
    if (ant->position.y > h)
        ant->position.y -= h;
    if (ant->position.x < 0.0f)
        ant->position.x += w;
    if (ant->position.y < 0.0f)
        ant->position.y += h;

    // Release pheromone
    int x = int(ant->position.x);
    int y = int(ant->position.y);
    if (x >= 0 && y >= 0 && x < w && y < h)
        _world.get<WorldComponent>()->antOnTop[y * w + x] = 1;
}

ATTA_CPU_GPU uint16_t Ant::sense(atta::vec2i pos) {
    uint32_t w = WorldComponent::width;
    uint32_t h = WorldComponent::height;

    auto& pheromones = _world.get<WorldComponent>()->pheromones;
    uint32_t time = _world.get<WorldComponent>()->time;

    uint16_t sum = 0;
    for (int offy = -1; offy <= 1; offy++)
        for (int offx = -1; offx <= 1; offx++) {
            int x = (pos.x + offx + w) % w;
            int y = (pos.y + offy + h) % h;
            if (x >= 0 && y >= 0 && x < w && y < h) {
                uint32_t pheromoneTime = pheromones[y * w + x];
                // Calculate amount of pheromone given the time difference
                uint32_t evaporated = pheromoneTime == 0 ? 255 : (time - pheromoneTime) / WorldComponent::evaporate;
                sum += evaporated >= 255 ? 0 : 255 - evaporated;
            }
        }

    return sum;
}
