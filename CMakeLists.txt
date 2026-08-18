cmake_minimum_required(VERSION 3.28)
project(TanksNeuralNet LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/)


set(BUILD_ENVIRONMENT "$ENV{BUILD_ENVIRON}") # set to Production when doing production builds
add_definitions(-DBUILD_ENVIRONMENT="${BUILD_ENVIRONMENT}")
message(INFO ": Building for ${BUILD_ENVIRONMENT}")

# for intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# for output
if(BUILD_ENVIRONMENT STREQUAL "development" )
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../releases/${CMAKE_PROJECT_VERSION}/)
endif()

file(REMOVE_RECURSE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}) # clear directory for new files to be built


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

