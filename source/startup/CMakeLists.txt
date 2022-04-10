
set(MODULE_SOURCES
        src/main.cpp)

add_library(startup OBJECT ${MODULE_SOURCES})

target_link_libraries(startup PUBLIC spdlog::spdlog mqtt)
