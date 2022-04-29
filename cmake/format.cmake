include_guard()


file(GLOB_RECURSE CLANG_FORMAT_FILES source/*.cpp source/*.hpp)
add_custom_target(
    clang-format
    COMMAND clang-format
    -style=file
    -i
    ${CLANG_FORMAT_FILES}
)