//--------------------------------------------------
// Ants
// antScript.h
// Date: 2022-08-20
// By Breno Cunha Queiroz
//--------------------------------------------------
#ifndef ANT_SCRIPT_H
#define ANT_SCRIPT_H
#include <atta/script/script.h>

namespace cmp = atta::component;
namespace scr = atta::script;

class AntScript : public scr::Script {
  public:
    void update(cmp::Entity entity, float dt) override;
};

ATTA_REGISTER_SCRIPT(AntScript)

#endif // ANT_SCRIPT_H
