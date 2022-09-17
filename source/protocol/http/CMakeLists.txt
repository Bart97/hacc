SET(TARGET_NAME http)
SET(TARGET_SOURCES
    src/EscapeString.cpp
    src/HttpRequest.cpp
    src/HttpRequestFactory.cpp)
SET(TARGET_HEADERS
    inc/protocol/http/EscapeString.hpp
    inc/protocol/http/HttpRequest.hpp
    inc/protocol/http/HttpRequestFactory.hpp
    inc/protocol/http/IHttpRequest.hpp
    inc/protocol/http/IHttpRequestFactory.hpp)

add_library(${TARGET_NAME} STATIC ${TARGET_SOURCES} ${TARGET_HEADERS})
target_include_directories(${TARGET_NAME} PUBLIC inc)

target_link_libraries(${TARGET_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${TARGET_NAME} LINK_PUBLIC ${CURLPP_LDFLAGS})

add_subdirectory(ut)
