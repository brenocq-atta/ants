//--------------------------------------------------
// Ants
// projectScript.h
// Date: 2022-08-20
// By Breno Cunha Queiroz
//--------------------------------------------------
#ifndef PROJECT_SCRIPT_H
#define PROJECT_SCRIPT_H
#include <atta/pch.h>
#include <atta/script/projectScript.h>
#include <atta/resource/resources/image.h>

class Project : public atta::script::ProjectScript {
  public:
    //---------- Simulation ----------//
    void onLoad() override;
    void onStart() override;
    void onStop() override;
    void onUpdateBefore(float dt) override;

    //---------- UI ----------//
    void onUIRender() override;

  private:
    atta::resource::Image* _bgImage;
};

ATTA_REGISTER_PROJECT_SCRIPT(Project)

#endif // PROJECT_SCRIPT_H
