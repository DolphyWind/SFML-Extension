cmake_minimum_required(VERSION 3.0.0)
set(SFEX_PROJECT_NAME SFEX)
project(${SFEX_PROJECT_NAME} VERSION 0.13.3)
include(GNUInstallDirs)

# Find SFML and enable c++14
set(CMAKE_CXX_STANDARD 14)
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system audio)

set(SFEX_TARGETS_FILENAME "${SFEX_PROJECT_NAME}Targets.cmake")
set(SFEX_CONFIG_FILENAME "${SFEX_PROJECT_NAME}Config.cmake")
set(SFEX_CONFIGVERSION_FILENAME "${SFEX_PROJECT_NAME}ConfigVersion.cmake")
set(SFEX_INSTALL_CMAKE_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${SFEX_PROJECT_NAME}")
set(SFEX_INCLUDE_FOLDER "include")

set( SFEX_HEADER_FILES
	${SFEX_INCLUDE_FOLDER}/SFEX/Config.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/General.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Managers.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Numeric.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Graphics.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/SFEX.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/General/Stopwatch.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/General/FilteringMethods.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/General/Keyboard.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/General/Mouse.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/General/Singleton.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Numeric/Vector2.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Numeric/Vector3.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Numeric/Math.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Numeric/Gradient.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Graphics/Color.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Graphics/RoundedRectangle.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Graphics/Ellipse.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Graphics/Squircle.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Managers/TextureManager.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Managers/SpriteManager.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Managers/SoundManager.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Managers/MusicManager.hpp
)
set( SFEX_SOURCE_FILES
    src/SFEX/General/Stopwatch.cpp
    src/SFEX/General/Keyboard.cpp
    src/SFEX/General/Mouse.cpp
    src/SFEX/General/Singleton.cpp
    src/SFEX/Numeric/Vector2.cpp
    src/SFEX/Numeric/Vector3.cpp
    src/SFEX/Numeric/Math.cpp
    src/SFEX/Numeric/Gradient.cpp
    src/SFEX/Graphics/Color.cpp
    src/SFEX/Graphics/RoundedRectangle.cpp
    src/SFEX/Graphics/Ellipse.cpp
    src/SFEX/Graphics/Squircle.cpp
    src/SFEX/Managers/TextureManager.cpp
    src/SFEX/Managers/SpriteManager.cpp
    src/SFEX/Managers/SoundManager.cpp
    src/SFEX/Managers/MusicManager.cpp
)

include(CMakePackageConfigHelpers)
configure_package_config_file("cmake/config.cmake.in"
                              "${CMAKE_CURRENT_BINARY_DIR}/${SFEX_CONFIG_FILENAME}"
                              INSTALL_DESTINATION ${SFEX_INSTALL_CMAKE_DIR}
                              PATH_VARS SFEX_INCLUDE_FOLDER)
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/${SFEX_CONFIGVERSION_FILENAME}"
                                 COMPATIBILITY SameMajorVersion)

add_library(${SFEX_PROJECT_NAME} STATIC ${SFEX_SOURCE_FILES})
target_include_directories(${SFEX_PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${SFEX_INCLUDE_FOLDER}>)
target_link_libraries(${SFEX_PROJECT_NAME} sfml-graphics sfml-system sfml-window sfml-audio)

export(TARGETS ${SFEX_PROJECT_NAME}
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${SFEX_TARGETS_FILENAME}")
export(PACKAGE ${SFEX_PROJECT_NAME})

install(TARGETS ${SFEX_PROJECT_NAME}
        EXPORT ${SFEX_PROJECT_NAME})
install(DIRECTORY ${SFEX_INCLUDE_FOLDER}/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ${SFEX_PROJECT_NAME}
        FILE ${SFEX_TARGETS_FILENAME}
        DESTINATION ${SFEX_INSTALL_CMAKE_DIR})
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${SFEX_CONFIG_FILENAME}"
              "${CMAKE_CURRENT_BINARY_DIR}/${SFEX_CONFIGVERSION_FILENAME}"
        DESTINATION ${SFEX_INSTALL_CMAKE_DIR})

