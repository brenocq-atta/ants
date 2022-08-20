//--------------------------------------------------
// Ants
// antComponent.h
// Date: 2022-08-20
// By Breno Cunha Queiroz
//--------------------------------------------------
#ifndef ANT_COMPONENT_H
#define ANT_COMPONENT_H
#include <atta/component/interface.h>

namespace cmp = atta::component;

struct AntComponent final : public cmp::Component {
    atta::vec2 position;
    float angle;
};
ATTA_REGISTER_COMPONENT(AntComponent);
template <>
cmp::ComponentDescription& cmp::TypedComponentRegistry<AntComponent>::getDescription();

#endif // ANT_COMPONENT_H
