SET(TARGET_NAME timer)
SET(TARGET_SOURCES
    src/Timer.cpp
    src/TimerManager.cpp)
SET(TARGET_HEADERS
    inc/timer/ITimer.hpp
    inc/timer/ITimerManager.hpp
    inc/timer/Timer.hpp
    inc/timer/TimerCallback.hpp
    inc/timer/TimerManager.hpp
    inc/timer/events/TimerExpiredEvent.hpp)

add_library(${TARGET_NAME} ${TARGET_SOURCES} ${TARGET_HEADERS})
target_include_directories(${TARGET_NAME} PUBLIC inc)

target_link_libraries(${TARGET_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${TARGET_NAME} PUBLIC event)

add_subdirectory(ut)
