cmake_minimum_required(VERSION 3.15.0)
set(SFEX_PROJECT_NAME SFEX)
project(${SFEX_PROJECT_NAME} VERSION 0.24.0)
include(GNUInstallDirs)
include(CTest)
enable_testing()

# Find SFML and enable c++17
set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system audio)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SFEX_TARGETS_FILENAME "${SFEX_PROJECT_NAME}Targets.cmake")
set(SFEX_CONFIG_FILENAME "${SFEX_PROJECT_NAME}Config.cmake")
set(SFEX_CONFIGVERSION_FILENAME "${SFEX_PROJECT_NAME}ConfigVersion.cmake")
set(SFEX_INSTALL_CMAKE_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${SFEX_PROJECT_NAME}")
set(SFEX_INCLUDE_FOLDER "include")
set(SFEX_SRC_FOLDER "src")

# set(SFEX_SRC_FOLDER "${CMAKE_SOURCE_DIR}/src")
# file(GLOB_RECURSE SFEX_HEADER_FILES "${CMAKE_SOURCE_DIR}/include/*.hpp")
# file(GLOB_RECURSE SFEX_SOURCE_FILES "${SFEX_SRC_FOLDER}/*.cpp")

set( SFEX_HEADER_FILES
	${SFEX_INCLUDE_FOLDER}/SFEX/Config.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/General.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Graphics.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Managers.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Numeric.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/SFEX.hpp

	${SFEX_INCLUDE_FOLDER}/SFEX/General/FilteringMethods.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/General/Joystick.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/General/Keyboard.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/General/Listener.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/General/Mouse.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/General/Multitype.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/General/Scene.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/General/Scheduler.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/General/Singleton.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/General/StaticClass.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/General/Stopwatch.hpp

	${SFEX_INCLUDE_FOLDER}/SFEX/Numeric/AngleSystem.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Numeric/Gradient.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Numeric/Math.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Numeric/Vector.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Numeric/Vector2.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Numeric/Vector3.hpp

	${SFEX_INCLUDE_FOLDER}/SFEX/Graphics/Animation.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Graphics/Color.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Graphics/Ellipse.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Graphics/RoundedRectangle.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Graphics/Squircle.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Graphics/Star.hpp

	${SFEX_INCLUDE_FOLDER}/SFEX/Managers/AnimationManager.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Managers/ManagerBase.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Managers/MusicManager.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Managers/OptionManager.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Managers/SceneManager.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Managers/SoundManager.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Managers/SpriteManager.hpp
	${SFEX_INCLUDE_FOLDER}/SFEX/Managers/TextureManager.hpp
)
set( SFEX_SOURCE_FILES
	${SFEX_SRC_FOLDER}/SFEX/General/Joystick.cpp
    ${SFEX_SRC_FOLDER}/SFEX/General/Keyboard.cpp
    ${SFEX_SRC_FOLDER}/SFEX/General/Listener.cpp
    ${SFEX_SRC_FOLDER}/SFEX/General/Mouse.cpp
    ${SFEX_SRC_FOLDER}/SFEX/General/Multitype.cpp
    ${SFEX_SRC_FOLDER}/SFEX/General/Singleton.cpp
    ${SFEX_SRC_FOLDER}/SFEX/General/Stopwatch.cpp

    ${SFEX_SRC_FOLDER}/SFEX/Numeric/AngleSystem.cpp
    
	${SFEX_SRC_FOLDER}/SFEX/Graphics/Animation.cpp
    ${SFEX_SRC_FOLDER}/SFEX/Graphics/Color.cpp
    ${SFEX_SRC_FOLDER}/SFEX/Graphics/Ellipse.cpp
    ${SFEX_SRC_FOLDER}/SFEX/Graphics/RoundedRectangle.cpp
    ${SFEX_SRC_FOLDER}/SFEX/Graphics/Squircle.cpp
    ${SFEX_SRC_FOLDER}/SFEX/Graphics/Star.cpp
    
    ${SFEX_SRC_FOLDER}/SFEX/Managers/AnimationManager.cpp
	${SFEX_SRC_FOLDER}/SFEX/Managers/ManagerBase.cpp
    ${SFEX_SRC_FOLDER}/SFEX/Managers/MusicManager.cpp
    ${SFEX_SRC_FOLDER}/SFEX/Managers/OptionManager.cpp
    ${SFEX_SRC_FOLDER}/SFEX/Managers/SceneManager.cpp
    ${SFEX_SRC_FOLDER}/SFEX/Managers/SoundManager.cpp
    ${SFEX_SRC_FOLDER}/SFEX/Managers/SpriteManager.cpp
    ${SFEX_SRC_FOLDER}/SFEX/Managers/TextureManager.cpp
)

# Thanks to Victoria Rudakova for the doxygen with CMake tutorial https://vicrucann.github.io/tutorials/quick-cmake-doxygen/
option(BUILD_DOCS "Build documentation" OFF)
if(BUILD_DOCS)
    # check if Doxygen is installed
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
	message(STATUS "Doxygen found successfully!")
	# set input and output files
	set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
	set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

	# request to configure the file
	configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
	message("Doxygen build started")

	# note the option ALL which allows to build the docs together with the application
	add_custom_target( doc_doxygen ALL
	    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
	    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	    COMMENT "Generating API documentation with Doxygen"
	    VERBATIM )
    else ()
	message(WARNING "CMake can't find Doxygen. Documentation won't be generated.")
    endif ()
else()
    message(STATUS "Building documentation is disabled. Documentation won't be generated.")
endif()

include(CMakePackageConfigHelpers)
configure_package_config_file("cmake/config.cmake.in"
                              "${CMAKE_CURRENT_BINARY_DIR}/${SFEX_CONFIG_FILENAME}"
                              INSTALL_DESTINATION ${SFEX_INSTALL_CMAKE_DIR}
                              PATH_VARS SFEX_INCLUDE_FOLDER)
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/${SFEX_CONFIGVERSION_FILENAME}"
                                 COMPATIBILITY SameMajorVersion)

option(SFEX_USE_UPDATE_BASED_INPUT_HANDLING "Normally, getXDown() and getXUp() functions can be called once per frame. Second and third calls will return false even if it should return true. This is because those functions update the internal state of the key. But in real world, you might need to call those functions more than once in a frame. If you enable this option, it updates internal state when the update is called." ON)

add_library(${SFEX_PROJECT_NAME} STATIC ${SFEX_SOURCE_FILES})
target_include_directories(${SFEX_PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${SFEX_INCLUDE_FOLDER}>)
if(SFEX_USE_UPDATE_BASED_INPUT_HANDLING)
target_compile_definitions(${SFEX_PROJECT_NAME} PRIVATE SFEX_USE_UPDATE_BASED_INPUT_HANDLING)    
endif(SFEX_USE_UPDATE_BASED_INPUT_HANDLING)

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

option(BUILD_TESTS "Build Tests" ON)

if(BUILD_TESTS)
	message(STATUS "Testing is enabled. To run tests, please use CTest executable.")
	add_subdirectory(tests)
else()
	message(STATUS "Testing is disabled.")
endif()
