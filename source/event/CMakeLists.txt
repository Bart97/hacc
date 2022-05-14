SET(TARGET_NAME event)
set(TARGET_SOURCES
    src/EventDispatcher.cpp)
set(TARGET_HEADERS
    inc/event/EventCallbackWrapper.hpp
    inc/event/EventDispatcher.hpp
    inc/event/EventWrapper.hpp
    inc/event/IEventDispatcher.hpp
    inc/event/IEventWrapper.hpp
    inc/event/IEventCallbackWrapper.hpp
    inc/event/EventCallbackWrapperFactory.hpp
    inc/event/EventCallback.hpp
    inc/event/EventUidGenerator.hpp
    inc/event/EventUID.hpp)

add_library(${TARGET_NAME} ${TARGET_SOURCES} ${TARGET_HEADERS})
target_link_libraries(${TARGET_NAME}
    PUBLIC
    itf
    spdlog::spdlog)
target_include_directories(${TARGET_NAME} PUBLIC inc)

add_subdirectory(ut)
