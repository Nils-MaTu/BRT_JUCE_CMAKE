# Mandatory line, sets the minimum version of CMake that should be used with this repository.
# I specified 3.22 because I trust it. However, currently I have 3.26 installed on my machine.
# To verify your version run
# $ cmake --version
cmake_minimum_required(VERSION 3.22)

# Sets a few variables, like PROJECT_NAME
project(plugin)

# Always use the newest C++ standard on green-field projects if possible.
set(CMAKE_CXX_STANDARD 23)

# I like to download the dependencies to the same folder as the project.
# If you want to install them system wide, set CPM_SOURCE_CACHE with the path to the dependencies
# either as an environment variable or pass it to the cmake script with -DCPM_SOURCE_CACHE=<path>.
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)
#set(CPM_SOURCE_CACHE "${CMAKE_CURRENT_SOURCE_DIR}/libs")

# Downloads CPM if not already downloaded. CPM is an easy-to-use package manager nicely integrated with CMake.
include(cmake/cpm.cmake)


CPMAddPackage(
        NAME LibMySofa
        GIT_TAG cmake
        GITHUB_REPOSITORY GrupoDiana/libmysofa
        SOURCE_DIR ${LIB_DIR}/libmysofa
)

CPMAddPackage(
        NAME json
        GIT_TAG develop
        GITHUB_REPOSITORY nlohmann/json
        SOURCE_DIR ${LIB_DIR}/nlohmann
)

# This commands downloads AND configures JUCE. It sets up some variables, like JUCE_SOURCE_DIR.
CPMAddPackage(
        NAME JUCE
        GIT_TAG 7.0.7
        VERSION 7.0.7
        GITHUB_REPOSITORY juce-framework/JUCE
        SOURCE_DIR ${LIB_DIR}/juce
)

set(nlohmann_json_DIR "${LIB_DIR}/nlohmann/build")
set(mysofa_DIR "${LIB_DIR}/libmysofa/build")


CPMAddPackage(
        NAME brt
        GIT_TAG origin/cmake
        VERSION 1.3
        GITHUB_REPOSITORY GrupoDiana/BRTLibrary
        SOURCE_DIR ${LIB_DIR}/brt
)

# This command allows running tests from the "build" folder (the one where CMake generates the project to).
enable_testing()

# Enables all warnings and treats warnings as errors.
# This needs to be added AFTER all the third-party dependencies.
if(MSVC)
    add_compile_options(/Wall /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Adds all the targets configured in the "plugin" folder.
add_subdirectory(plugin)

