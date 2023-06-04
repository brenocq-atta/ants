//--------------------------------------------------
// Ants
// ant.h
// Date: 2023-05-25
// By Breno Cunha Queiroz
//--------------------------------------------------
#ifndef ANTS_ANT_H
#define ANTS_ANT_H
#include <atta/script/scripts/controller.h>
#include <atta/script/registry/controllerRegistry.h>

class Ant : public atta::script::Controller {
  public:
    ATTA_CPU_GPU void update();

  private:
    ATTA_CPU_GPU uint16_t sense(atta::vec2i pos);

    cmp::Entity _world;
};

#ifndef __NVCC__
ATTA_REGISTER_CONTROLLER(Ant)
#endif

#endif // ANTS_ANT_H
