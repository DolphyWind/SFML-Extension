cmake_minimum_required(VERSION 3.0.0)
set(SFEX_PROJECT_NAME SFEX)
project(${SFEX_PROJECT_NAME} VERSION 0.5.0)
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system audio)

set( SFEX_HEADER_FILES
	include/SFEX/Config.hpp
	include/SFEX/General.hpp
	include/SFEX/Managers.hpp
	include/SFEX/Numeric.hpp
	include/SFEX/Graphics.hpp
	include/SFEX/SFEX.hpp
	include/SFEX/General/Stopwatch.hpp
	include/SFEX/Numeric/Vector2.hpp
	include/SFEX/Numeric/Vector3.hpp
	include/SFEX/Numeric/Math.hpp
	include/SFEX/Numeric/Gradient.hpp
	include/SFEX/Graphics/Color.hpp
)
set( SFEX_SOURCE_FILES
    src/SFEX/General/Stopwatch.cpp
    src/SFEX/Numeric/Vector2.cpp
    src/SFEX/Numeric/Vector3.cpp
    src/SFEX/Numeric/Math.cpp
    src/SFEX/Numeric/Gradient.cpp
    src/SFEX/Graphics/Color.cpp
)

add_library(${SFEX_PROJECT_NAME} STATIC ${SFEX_SOURCE_FILES})
target_include_directories(${SFEX_PROJECT_NAME} PUBLIC include)
target_link_libraries(${SFEX_PROJECT_NAME} sfml-graphics sfml-system sfml-window sfml-audio)
install(TARGETS ${SFEX_PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

