//--------------------------------------------------
// Ants
// system.cpp
// Date: 2022-08-20
// By Breno Cunha Queiroz
//--------------------------------------------------
#include "system.h"
#include "antComponent.h"
#include "worldComponent.h"
#include <atta/component/interface.h>

const cmp::Entity world(0);
const cmp::Entity antPrototype(1);

void System::onLoad() {
    LOG_DEBUG("System", "onLoad");

    uint32_t w = WorldComponent::width;
    uint32_t h = WorldComponent::height;

    res::Image::CreateInfo info;
    info.width = w;
    info.height = h;
    info.format = res::Image::Format::RGBA8;
    _bgImage = res::create<res::Image>("background", info);

    uint8_t* data = _bgImage->getData();
    for (int i = 0; i < w * h * 4; i += 4) {
        data[i] = data[i + 1] = data[i + 2] = 0;
        data[i + 3] = 255;
    }
    _bgImage->update();
}

void System::onUnload() { LOG_DEBUG("System", "onUnload"); }

void System::onUIRender() {
    // Get pheromones
    uint32_t w = WorldComponent::width;
    uint32_t h = WorldComponent::height;
    uint32_t time = world.get<WorldComponent>()->time;
    auto& pheromones = world.get<WorldComponent>()->pheromones;

    // Update texture
    uint8_t* data = _bgImage->getData();
    for (int i = 0; i < w * h; i++) {
        uint8_t evaporated = pheromones[i] == 0 ? 255 : (time - pheromones[i]) / WorldComponent::evaporate;
        data[i * 4] = evaporated >= 255 ? 0 : 255 - evaporated;
        data[i * 4 + 1] = 0;
        data[i * 4 + 2] = 0;
    }
    _bgImage->update();
}
