//--------------------------------------------------
// Ants
// world.h
// Date: 2022-08-20
// By Breno Cunha Queiroz
//--------------------------------------------------
#ifndef ANTS_WORLD_H
#define ANTS_WORLD_H
#include <atta/resource/interface.h>
#include <atta/resource/resources/image.h>
#include <atta/script/registry/worldRegistry.h>
#include <atta/script/scripts/world.h>
#include <atta/component/entity.h>

class World : public atta::script::World {
  public:
    //---------- Simulation ----------//
    ATTA_CPU_GPU void onStart() override;
    ATTA_CPU_GPU void onStop() override;


    ATTA_CPU_GPU void onUpdateBefore() override;
    ATTA_CPU_GPU void onUpdateAfter() override;

  private:
    cmp::Entity _world;
    cmp::Entity _antPrototype;

    float _lastEvaporate;
    float _lastBlur;
};

#ifndef __NVCC__
ATTA_REGISTER_WORLD(World)
#endif

#endif // ANTS_WORLD_H
