cmake_minimum_required(VERSION 3.0.0)
project(SceneManagerExample VERSION 1.0.0)

set(PROGRAM_NAME scenemanager_example)
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system audio)
find_package(SFEX REQUIRED)

file(GLOB CPP_FILES "./src/*.cpp")

add_executable(${PROGRAM_NAME} ${CPP_FILES})
target_include_directories(${PROGRAM_NAME} PUBLIC include)
target_link_libraries(${PROGRAM_NAME} sfml-graphics sfml-system sfml-window sfml-audio SFEX)
