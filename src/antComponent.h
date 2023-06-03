//--------------------------------------------------
// Ants
// antComponent.h
// Date: 2022-08-20
// By Breno Cunha Queiroz
//--------------------------------------------------
#ifndef ANTS_ANT_COMPONENT_H
#define ANTS_ANT_COMPONENT_H
#include <atta/component/components/component.h>

struct AntComponent final : public atta::component::Component {
    atta::vec2 position;
    float angle;
};

#ifndef __NVCC__
#include <atta/component/registry/typedRegistry.h>
ATTA_REGISTER_COMPONENT(AntComponent);
#endif

// template <>
// cmp::ComponentDescription& cmp::TypedRegistry<AntComponent>::getDescription();

#endif // ANTS_ANT_COMPONENT_H
