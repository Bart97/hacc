SET(TARGET_NAME protocol_metrics_interface)
set(TARGET_SOURCES
    src/Entry.cpp
    src/DummyMetricsServer.cpp)
set(TARGET_HEADERS
    inc/protocol/metrics/DummyMetricsServer.hpp
    inc/protocol/metrics/Entry.hpp
    inc/protocol/metrics/IMetricsServer.hpp)

add_library(${TARGET_NAME} STATIC ${TARGET_SOURCES} ${TARGET_HEADERS})
target_link_libraries(${TARGET_NAME}
    PUBLIC
    itf
    spdlog::spdlog)
target_include_directories(${TARGET_NAME} PUBLIC inc)

add_subdirectory(ut)
