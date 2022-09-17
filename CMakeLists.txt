cmake_minimum_required(VERSION 3.12)
project(ants VERSION 1.0.0 LANGUAGES CXX)
find_package(atta 0.2.0.0 REQUIRED)

atta_add_target(ant_component "src/antComponent.cpp")
atta_add_target(world_component "src/worldComponent.cpp")

atta_add_target(ant_script "src/antScript.cpp")
target_link_libraries(ant_script PUBLIC ant_component world_component)

atta_add_target(project_script "src/projectScript.cpp")
target_link_libraries(project_script PUBLIC ant_component world_component)
