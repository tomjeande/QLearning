cmake_minimum_required(VERSION 3.20)    # Minimal CMake version required
project(qlearning LANGUAGES CXX)        # Name the project and specifies that only C++ is used (no C)

# Set C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Write a json file with all the compiling commands -- useful for the C++ linter
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Target definitions

## Target = qlearning_warnings
add_library(qlearning_warnings INTERFACE)
set(QLEARNING_WARNINGS -Wall -Wextra -Wpedantic -Wshadow -Wconversion) # List of warnings we want to enable
target_compile_options(qlearning_warnings INTERFACE
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
)

## Target = qlearning_core
add_library(qlearning_core STATIC 
    src/csv_logger.cpp 
    src/grid_world.cpp 
    src/qlearning_agent.cpp
    src/render.cpp
    src/trainer.cpp
)
target_include_directories(qlearning_core PUBLIC include)
target_link_libraries(qlearning_core PRIVATE qlearning_warnings)

## Target = train
add_executable(train apps/train_main.cpp)
target_link_libraries(train PRIVATE qlearning_core qlearning_warnings)

## Target = unit_tests
include(FetchContent) # Load the CMake module responsible for downloading dependencies
FetchContent_Declare(googletest 
    URL https://github.com/google/googletest/archive/refs/tags/v1.18.0.zip 
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(unit_tests tests/test_types.cpp)
target_link_libraries(unit_tests PRIVATE qlearning_core GTest::gtest_main qlearning_warnings)
include(GoogleTest)
gtest_discover_tests(unit_tests)
