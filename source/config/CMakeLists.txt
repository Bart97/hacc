SET(TARGET_NAME config)
SET(TARGET_SOURCES
    src/ConfigFile.cpp)
SET(TARGET_HEADERS
    inc/config/ConfigFile.hpp)

add_library(${TARGET_NAME} STATIC ${TARGET_SOURCES} ${TARGET_HEADERS})
target_include_directories(${TARGET_NAME} PUBLIC
    inc
    ${JSONCPP_INCLUDE_DIRS})

target_link_libraries(${TARGET_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${TARGET_NAME} PUBLIC
    ${JSONCPP_LIBRARIES})

#add_subdirectory(ut)
