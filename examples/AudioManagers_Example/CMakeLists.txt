cmake_minimum_required(VERSION 3.0.0)
project(AudioManagersExample VERSION 1.0.0)

set(PROGRAM_NAME audiomanagers_example)
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system audio)
find_package(SFEX REQUIRED)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB CPP_FILES "./src/*.cpp")

add_executable(${PROGRAM_NAME} ${CPP_FILES})
target_include_directories(${PROGRAM_NAME} PUBLIC include)
target_link_libraries(${PROGRAM_NAME} sfml-graphics sfml-system sfml-window sfml-audio SFEX)
