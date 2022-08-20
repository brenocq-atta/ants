//--------------------------------------------------
// Ants
// antScript.cpp
// Date: 2022-08-20
// By Breno Cunha Queiroz
//--------------------------------------------------
#include "antScript.h"
#include "antComponent.h"
#include "worldComponent.h"

const cmp::Entity world(0);

uint16_t sense(atta::vec2i pos, uint8_t f) {
    uint32_t w = WorldComponent::width;
    uint32_t h = WorldComponent::height;

    auto pheromone = world.get<WorldComponent>()->pheromones[f];

    uint16_t sum;
    for (int offy = -1; offy <= 1; offy++)
        for (int offx = -1; offx <= 1; offx++) {
            int x = (pos.x + offx + w) % w;
            int y = (pos.y + offy + h) % h;
            sum += pheromone[y * w + x];
            world.get<WorldComponent>()->pheromones[1][y * w + x] = 10;
        }

    return sum;
}

void AntScript::update(cmp::Entity entity, float dt) {
    AntComponent* ant = entity.get<AntComponent>();

    float a0 = ant->angle;
    float a1 = ant->angle + M_PI / 3;
    float a2 = ant->angle - M_PI / 3;
    float r = 5.0f;
    uint8_t f = 0;

    uint16_t s0 = sense(ant->position + atta::vec2(cos(a0), sin(a0)) * r, f);
    uint16_t s1 = sense(ant->position + atta::vec2(cos(a1), sin(a1)) * r, f);
    uint16_t s2 = sense(ant->position + atta::vec2(cos(a2), sin(a2)) * r, f);
    // s0 += (rand() / float(RAND_MAX)) * 5;
    // s1 += (rand() / float(RAND_MAX)) * 5;
    // s2 += (rand() / float(RAND_MAX)) * 5;
    //  LOG_DEBUG("AntScript", "Ant $0 $1 $2", entity.getCloneId(), s0, s1, s2);

    // if (s1 > s0 && s1 > s2)
    //     ant->angle += (a1 - a0) * dt;
    // else if (s2 > s0 && s2 > s1)
    //     ant->angle += (a2 - a0) * dt;
    ant->angle = (a0 * s0 + (a0 + (a1 - a0) * dt) * s1 + (a0 + (a2 - a0) * dt) * s2) / (s0 + s1 + s2);
    ant->angle += ((rand() / float(RAND_MAX)) - 0.5f) * 30 * dt;
    // ant->angle +=

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
