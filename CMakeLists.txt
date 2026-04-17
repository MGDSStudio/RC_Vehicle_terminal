cmake_minimum_required(VERSION 3.28.3)
project(RC_Vehicle_terminal)

set(CMAKE_CXX_STANDARD 17)

# 1. Вместо FetchContent ищем установленную в системе библиотеку
# На Raspberry Pi: sudo apt install libsdl3-dev (если доступно)
# Или соберите/установите её один раз вручную: make install
find_package(SDL3 REQUIRED)

include_directories(include)

if(EXISTS "/proc/device-tree/model")
    file(READ "/proc/device-tree/model" DEVICE_MODEL)
    if(DEVICE_MODEL MATCHES "Raspberry Pi")
        set(IS_RPI TRUE)
    endif()
endif()

# Убираем GLOB_RECURSE, если файлы перечислены ниже вручную,
# чтобы избежать дублирования и лишнего потребления памяти
file(GLOB_RECURSE SOURCES
        "src/*.cpp"
        "src/*.h"
        "src/*.hpp"
)

add_executable(RC_Vehicle_terminal ${SOURCES}
        src/CompletionController.cpp
        src/CompletionController.h)

# 3. Привязываем найденную в системе SDL3
target_link_libraries(RC_Vehicle_terminal PRIVATE SDL3::SDL3)

add_custom_command(TARGET RC_Vehicle_terminal POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/data"
        "$<TARGET_FILE_DIR:RC_Vehicle_terminal>/data"
        COMMENT "Data copy in the output dir..."
)

if(IS_RPI)
    message(STATUS "Configuring for Raspberry Pi...")
    find_library(PIGPIO_LIB pigpio)
    if(PIGPIO_LIB)
        # ВНИМАНИЕ: Исправлено имя цели с 'main' на 'RC_Vehicle_terminal'
        target_link_libraries(RC_Vehicle_terminal PRIVATE ${PIGPIO_LIB} pthread rt)
        target_compile_definitions(RC_Vehicle_terminal PRIVATE RPI_BUILD IS_RPI)
    else()
        message(WARNING "pigpio not found!")
    endif()
endif()

if(WIN32)
    add_custom_command(TARGET RC_Vehicle_terminal POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL3::SDL3>
            $<TARGET_FILE_DIR:RC_Vehicle_terminal>
    )
endif()
