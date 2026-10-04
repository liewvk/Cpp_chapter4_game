cmake_minimum_required(VERSION 3.28)

project(WelcomeGame LANGUAGES CXX)

include(FetchContent)

# Build only the SFML features needed for this example.
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "" FORCE)

# Download a fixed SFML release.
FetchContent_Declare(
    SFML
    URL https://github.com/SFML/SFML/archive/refs/tags/3.0.2.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(SFML)

# Define the application.
add_executable(WelcomeGame src/main.cpp)

target_compile_features(WelcomeGame PRIVATE cxx_std_17)

set_target_properties(
    WelcomeGame
    PROPERTIES
    CXX_EXTENSIONS OFF
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(
    WelcomeGame
    PRIVATE SFML::Graphics
)

# Locate assets reliably during development.
target_compile_definitions(
    WelcomeGame
    PRIVATE GAME_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets"
)
