cmake_minimum_required(VERSION 3.28)
project(TanksNeuralNet LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(BUILD_ENVIRONMENT "$ENV{BUILD_ENVIRON}") # set to Production when doing production builds
add_definitions(-DBUILD_ENVIRONMENT="${BUILD_ENVIRONMENT}")
message(INFO ": Building for ${BUILD_ENVIRONMENT}")

# for intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)





include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp)

target_compile_features(main PRIVATE cxx_std_17)

# add parts
add_subdirectory(src)
target_link_libraries(implementation PUBLIC SFML::Graphics)
target_link_libraries(main PRIVATE implementation)

add_custom_command(
    TARGET main POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_SOURCE_DIR}/assets" "${CMAKE_CURRENT_BINARY_DIR}/assets"
    COMMENT "Symlinking assets to build directory"
)
