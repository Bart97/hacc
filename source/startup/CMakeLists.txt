
set(MODULE_SOURCES
        src/main.cpp)

add_library(startup OBJECT ${MODULE_SOURCES})

target_link_libraries(startup PUBLIC
    spdlog::spdlog
    event
    http
    mqtt
    config
    core
    metrics
    protocol_metrics_influxdb
    timer
    zigbeemqtt)
