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
    float dt = 0.015;
    AntComponent* ant = get<AntComponent>();
    _world = cmp::Entity(0);

    float a0 = ant->angle;
    float a1 = ant->angle + M_PI / 3;
    float a2 = ant->angle - M_PI / 3;
    float r = 5.0f;
    uint8_t f = 0;

    // Sense pheromone
    uint16_t s0 = sense(ant->position + atta::vec2(cos(a0), sin(a0)) * r, f);
    uint16_t s1 = sense(ant->position + atta::vec2(cos(a1), sin(a1)) * r, f);
    uint16_t s2 = sense(ant->position + atta::vec2(cos(a2), sin(a2)) * r, f);

    // Change angle
    if (s0 + s1 + s2 != 0) {
        ant->angle = (a0 * s0 + (a0 + (a1 - a0) * dt) * s1 + (a0 + (a2 - a0) * dt) * s2) / (s0 + s1 + s2);
        ant->angle += 0.0f; //((rand() / float(RAND_MAX)) - 0.5f) * 10 * dt;
    }

    // Change position
    ant->position.x += (cos(ant->angle)) * dt;
    ant->position.y += (sin(ant->angle)) * dt;

    // Wrap angle
    if (ant->angle > M_PI * 2)
        ant->angle -= M_PI * 2;
    if (ant->angle < 0)
        ant->angle += M_PI * 2;

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
}

ATTA_CPU_GPU uint16_t Ant::sense(atta::vec2i pos, uint8_t f) {
    uint32_t w = WorldComponent::width;
    uint32_t h = WorldComponent::height;

    auto& pheromone = _world.get<WorldComponent>()->pheromones[f];

    uint16_t sum = 0;
    for (int offy = -1; offy <= 1; offy++)
        for (int offx = -1; offx <= 1; offx++) {
            int x = (pos.x + offx + w) % w;
            int y = (pos.y + offy + h) % h;
            if (x >= 0 && y >= 0 && x < w && y < h)
                sum += pheromone[y * w + x];
        }

    return sum;
}
