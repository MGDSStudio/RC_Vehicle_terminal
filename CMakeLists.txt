cmake_minimum_required(VERSION 3.31)
project(RC_Vehicle_terminal)

set(CMAKE_CXX_STANDARD 17)



# 1. Fetch SDL3 from GitHub
include(FetchContent)
FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL
        GIT_TAG main
)
FetchContent_MakeAvailable(SDL3)
# 2. Add your executable
add_executable(RC_Vehicle_terminal src/main.cpp)

# 3. Link SDL3
# SDL3 provides a unified target: SDL3::SDL3
target_link_libraries(RC_Vehicle_terminal PRIVATE SDL3::SDL3)

# 4. Copy DLL to output folder (Windows only)
if(WIN32)
    add_custom_command(TARGET RC_Vehicle_terminal POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL3::SDL3>
            $<TARGET_FILE_DIR:RC_Vehicle_terminal>
    )
endif()