//--------------------------------------------------
// Ants
// system.h
// Date: 2023-05-03
// By Breno Cunha Queiroz
//--------------------------------------------------
#ifndef ANTS_SYSTEM_H
#define ANTS_SYSTEM_H
#include <atta/resource/interface.h>
#include <atta/resource/resources/image.h>
#include <atta/script/registry/systemRegistry.h>
#include <atta/script/scripts/system.h>

class System : public atta::script::System {
  public:
    void onLoad() override;
    void onUnload() override;
    void onUIRender() override;

  private:
    atta::resource::Image* _bgImage;
    float _lastEvaporate;
    float _lastBlur;
};

ATTA_REGISTER_SYSTEM(System)

#endif // ANTS_SYSTEM_H
