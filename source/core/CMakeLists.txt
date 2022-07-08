SET(TARGET_NAME core)
set(TARGET_SOURCES
    src/DeviceManager.cpp)
set(TARGET_HEADERS
    inc/core/DeviceManager.hpp)

add_library(${TARGET_NAME} ${TARGET_SOURCES} ${TARGET_HEADERS})
target_link_libraries(${TARGET_NAME}
    PUBLIC
    itf
    spdlog::spdlog)
target_include_directories(${TARGET_NAME} PUBLIC inc)

add_subdirectory(ut)
