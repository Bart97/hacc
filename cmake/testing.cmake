include_guard()

enable_testing()

set(UT_BUILD_TARGET UT_build)

add_custom_target(UT ${CMAKE_CTEST_COMMAND})

add_custom_target(${UT_BUILD_TARGET})
add_dependencies(UT ${UT_BUILD_TARGET})
