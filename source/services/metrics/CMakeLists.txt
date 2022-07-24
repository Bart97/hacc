SET(TARGET_NAME metrics)
set(TARGET_SOURCES
    src/MetricsService.cpp)
set(TARGET_HEADERS
    inc/services/metrics/MetricsService.hpp)

add_library(${TARGET_NAME} STATIC ${TARGET_SOURCES} ${TARGET_HEADERS})
target_link_libraries(${TARGET_NAME}
    PUBLIC
    itf
    timer
    protocol_metrics_interface
    spdlog::spdlog)
target_include_directories(${TARGET_NAME} PUBLIC inc)

add_subdirectory(ut)
