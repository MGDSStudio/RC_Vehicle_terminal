cmake_minimum_required(VERSION 3.31)
project(RC_Vehicle_terminal)

set(CMAKE_CXX_STANDARD 17)



# 1. Fetch SDL3 from GitHub
include_directories(include)
include(FetchContent)
FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL
        GIT_TAG main
)
FetchContent_MakeAvailable(SDL3)

if(EXISTS "/proc/device-tree/model")
    file(READ "/proc/device-tree/model" DEVICE_MODEL)
    if(DEVICE_MODEL MATCHES "Raspberry Pi")
        set(IS_RPI TRUE)
    endif()
endif()

file(GLOB_RECURSE SOURCES
        "src/*.cpp"
        "src/*.h"
        "src/*.hpp"
)

# Используем переменную SOURCES вместо перечисления файлов
add_executable(RC_Vehicle_terminal ${SOURCES}
        src/MainController.cpp
        src/MainController.h
        src/gamepad/GamepadController.cpp
        src/gamepad/GamepadController.h
        src/gamepad/KeyboardController.cpp
        src/gamepad/KeyboardController.h
        src/gamepad/InputController.h
        src/gamepad/KeyboardDataStruct.cpp
        src/gamepad/KeyboardDataStruct.h
        src/gpio/ReleasePin.h
        src/gpio/ReleasePinHardware.cpp
        src/gpio/ReleasePinHardware.h
        src/gpio/ReleasePinSoftware.cpp
        src/gpio/ReleasePinSoftware.h)



# 3. Link SDL3
# SDL3 provides a unified target: SDL3::SDL3
target_link_libraries(RC_Vehicle_terminal PRIVATE SDL3::SDL3)

add_custom_command(TARGET RC_Vehicle_terminal POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/data"
        "$<TARGET_FILE_DIR:RC_Vehicle_terminal>/data"
        COMMENT "Data copy in the output dir..."
)

if(IS_RPI)
    message(STATUS "Configuring for Raspberry Pi...")
    # Ищем pigpio (она должна быть установлена в системе: sudo apt install pigpio)
    find_library(PIGPIO_LIB pigpio)
    if(PIGPIO_LIB)
        target_link_libraries(main PRIVATE ${PIGPIO_LIB} pthread rt)
        # Добавляем макрос для кода, чтобы можно было использовать #ifdef RPI_BUILD
        target_compile_definitions(main PRIVATE RPI_BUILD)
    else()
        message(WARNING "pigpio not found! GPIO features might not work.")
    endif()
endif()

# 4. Copy DLL to output folder (Windows only)
if(WIN32)
    add_custom_command(TARGET RC_Vehicle_terminal POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL3::SDL3>
            $<TARGET_FILE_DIR:RC_Vehicle_terminal>
    )
endif()