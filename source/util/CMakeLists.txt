SET(TARGET_NAME util)
set(TARGET_HEADERS
    inc/util/JsonParser.hpp)

set(TARGET_SOURCES
    src/JsonParser.cpp)

add_library(${TARGET_NAME} STATIC ${TARGET_HEADERS} ${TARGET_SOURCES})
target_include_directories(${TARGET_NAME} PUBLIC
    inc
    ${JSONCPP_INCLUDE_DIRS})

target_link_libraries(${TARGET_NAME} PUBLIC
    ${JSONCPP_LIBRARIES})

#add_subdirectory(ut)
