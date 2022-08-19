SET(TARGET_NAME protocol_metrics_influxdb)
set(TARGET_SOURCES
    src/InfluxdbConfigProvider.cpp
    src/InfluxdbMetricsServer.cpp
    src/InfluxdbMetricsServerFactory.cpp
    src/influxdb/Point.cpp
    src/influxdb/v2/InfluxdbApiV2.cpp)
set(TARGET_HEADERS
    inc/protocol/metrics/IInfluxdbConfigProvider.hpp
    inc/protocol/metrics/InfluxdbConfigProvider.hpp
    inc/protocol/metrics/InfluxdbMetricsServer.hpp
    inc/protocol/metrics/InfluxdbMetricsServerFactory.hpp
    inc/protocol/metrics/influxdb/IInfluxdbApi.hpp
    inc/protocol/metrics/influxdb/Point.hpp
    inc/protocol/metrics/influxdb/v2/InfluxdbApiV2.hpp)

add_library(${TARGET_NAME} ${TARGET_SOURCES} ${TARGET_HEADERS})
target_link_libraries(${TARGET_NAME}
    PUBLIC
    config
    itf
    protocol_metrics_interface
    spdlog::spdlog
    PRIVATE
    InfluxData::InfluxDB
    http)
target_include_directories(${TARGET_NAME} PUBLIC inc)

add_subdirectory(ut)
