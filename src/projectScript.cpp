//--------------------------------------------------
// Ants
// projectScript.cpp
// Date: 2022-08-20
// By Breno Cunha Queiroz
//--------------------------------------------------
#include "projectScript.h"
#include "antComponent.h"
#include "worldComponent.h"
#include <atta/resource/interface.h>
#include <atta/resource/resources/image.h>

namespace rsc = atta::resource;
namespace cmp = atta::component;

const cmp::Entity world(0);
const cmp::Entity antPrototype(1);

void Project::onLoad() {
    rsc::Image::CreateInfo info;
    info.width = WorldComponent::width;
    info.height = WorldComponent::height;
    info.format = rsc::Image::Format::RGBA8;
    _bgImage = rsc::create<rsc::Image>("background", info);

    resetWorld();
}

void Project::onStart() {
    srand(42); // Repeatable simulations

    // Init ants
    for (cmp::Entity ant : cmp::getFactory(antPrototype)->getClones()) {
        AntComponent* a = ant.get<AntComponent>();
        a->position = atta::vec2(rand() / float(RAND_MAX) * 100, rand() / float(RAND_MAX) * 100);
        a->angle = rand() / float(RAND_MAX) * M_PI * 2;
    }
}

void Project::onStop() {
    resetWorld();
}

void Project::onUpdateBefore(float dt) {
    uint32_t w = WorldComponent::width;
    uint32_t h = WorldComponent::height;
    auto& pheromones = world.get<WorldComponent>()->pheromones;

    _lastBlur += dt;
    _lastEvaporate += dt;

    // Blur
    if (_lastBlur >= world.get<WorldComponent>()->blur) {
        _lastBlur = 0;
        for (int f = 0; f < WorldComponent::numPheromones; f++)
            for (int x = 0; x < w; x++) {
                for (int y = 0; y < h; y++) {
                    int sum = 0;
                    for (int yn = y - 1; yn <= y + 1; yn++) {
                        for (int xn = x - 1; xn <= x + 1; xn++) {
                            if (yn >= 0 && xn >= 0 && yn < h && xn < w)
                                sum += pheromones[f][yn * w + xn];
                        }
                    }
                    int old = pheromones[f][y * w + x];
                    pheromones[f][y * w + x] = old * 0.9f + (sum / 9.0f) * 0.1f;
                }
            }
    }

    // Evaporate
    if (_lastEvaporate >= world.get<WorldComponent>()->evaporate) {
        _lastEvaporate = 0;
        for (int f = 0; f < WorldComponent::numPheromones; f++)
            for (int i = 0; i < w * h; i++)
                pheromones[f][i] = std::max(int(pheromones[f][i]) - 1, 0);
    }

    // Draw ants
    for (cmp::Entity ant : cmp::getFactory(antPrototype)->getClones()) {
        AntComponent* a = ant.get<AntComponent>();
        int x = int(a->position.x);
        int y = int(a->position.y);
        pheromones[0][y * w + x] = 255;
    }

    // Update texture
    uint8_t* data = _bgImage->getData();
    for (int i = 0; i < w * h; i++) {
        data[i * 4] = pheromones[0][i];
        data[i * 4 + 1] = pheromones[1][i];
        data[i * 4 + 2] = pheromones[2][i];
    }
    _bgImage->update();
}

void Project::onUIRender() {}

void Project::resetWorld() {
    _lastEvaporate = 0;
    _lastBlur = 0;

    uint32_t w = WorldComponent::width;
    uint32_t h = WorldComponent::height;
    for (auto& f : world.get<WorldComponent>()->pheromones)
        for (int i = 0; i < w * h; i++)
            f[i] = 0;

    uint8_t* data = _bgImage->getData();
    for (int i = 0; i < w * h * 4; i += 4) {
        data[i] = data[i + 1] = data[i + 2] = 0;
        data[i + 3] = 255;
    }
    _bgImage->update();
}
