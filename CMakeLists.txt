cmake_minimum_required(VERSION 3.12)
project(ants VERSION 1.0.0 LANGUAGES CXX CUDA)
find_package(atta 0.4.0.0 REQUIRED)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CUDA_SEPARABLE_COMPILATION ON)

atta_add_target(ant_component "src/antComponent.cpp")
atta_add_target(world_component "src/worldComponent.cpp")

atta_add_target(ant "src/ant.cpp")
target_link_libraries(ant PUBLIC ant_component world_component)
 
atta_add_target(world "src/world.cpp")
target_link_libraries(world PUBLIC ant_component world_component)

atta_add_target(system "src/system.cpp")
target_link_libraries(system PUBLIC ant_component world_component)

#set_source_files_properties("src/ant.cpp;src/world.cpp" PROPERTIES LANGUAGE CUDA)

#set(ANTS_SOURCE
#    src/ant.cpp
#    src/antComponent.cpp
#    src/world.cpp
#    src/worldComponent.cpp
#)
#
#atta_add_target(ants ${ANTS_SOURCE})
