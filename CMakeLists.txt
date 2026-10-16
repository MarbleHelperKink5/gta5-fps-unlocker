cmake_minimum_required(VERSION 3.22)
project(gta5-fps-unlocker VERSION 2.4.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(gta5-optimizer
    src/main.cpp
    src/core/optimizer_core.cpp
    src/core/config_loader.cpp
    src/services/memory_service.cpp
    src/handlers/patch_handler.cpp
    src/utils/logger.cpp
    src/utils/signature_scanner.cpp
    src/modules/fps_unlock/fps_unlock.cpp
    src/modules/stutter_fix/stutter_fix.cpp
    src/modules/shader_boost/shader_boost.cpp
    src/overlay/overlay_renderer.cpp
    src/injector/injector.cpp
)

target_include_directories(gta5-optimizer PRIVATE src)
target_link_libraries(gta5-optimizer PRIVATE d3d11 dxgi)

add_executable(test_patch_handler tests/test_patch_handler.cpp src/handlers/patch_handler.cpp src/services/memory_service.cpp src/utils/logger.cpp)
target_include_directories(test_patch_handler PRIVATE src)

add_executable(test_signature_scanner tests/test_signature_scanner.cpp src/utils/signature_scanner.cpp src/services/memory_service.cpp src/utils/logger.cpp)
target_include_directories(test_signature_scanner PRIVATE src)

enable_testing()
add_test(NAME patch_handler COMMAND test_patch_handler)
add_test(NAME sig_scanner COMMAND test_signature_scanner)