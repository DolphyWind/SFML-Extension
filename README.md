**THIS LIBRARY IS WORK IN PROGRESS. ANY FEATURE CAN CHANGE IN ANYTIME.**

# SFEX - SFML Extended
SFML Extended is a set of classes/functions to speed up SFML Game development.

# Build Status
[![Linux Build](https://github.com/DolphyWind/SFML-Extended/actions/workflows/linux_build.yml/badge.svg)](https://github.com/DolphyWind/SFML-Extended/actions/workflows/linux_build.yml)  
[![Windows Build](https://github.com/DolphyWind/SFML-Extended/actions/workflows/windows_build.yml/badge.svg)](https://github.com/DolphyWind/SFML-Extended/actions/workflows/windows_build.yml)  
[![MacOS build](https://github.com/DolphyWind/SFML-Extended/actions/workflows/mac_build.yml/badge.svg)](https://github.com/DolphyWind/SFML-Extended/actions/workflows/mac_build.yml)  
[![Building Documentation](https://github.com/DolphyWind/SFML-Extended/actions/workflows/build_docs.yml/badge.svg)](https://github.com/DolphyWind/SFML-Extended/actions/workflows/build_docs.yml)

# What This Library Provides
SFEX currently contains 4 modules: General, Graphics, Managers and Numeric.

- **General:** Classes that doesn't fit into other modules.
    - Joystick - Simple joystick class for detecting and proccessing the joystick input. Only contains static methods.
    - Keyboard - Simple keyboard class for detecting and proccessing the keyboard input. Only contains static methods.
    - Listener - Listener class that can be instantiated unlike sf::Listener.
    - Mouse - Simple mouse class for detecting and proccessing the mouse input. Only contains static methods.
    - Scene - Base scene class.
    - Singleton - A singleton base class. 
    - Stopwatch - A stopwatch class. Acts like sf::Clock but can be paused and resumed.
- **Graphics:** Classes that are related to graphics.
    - Animation - Simple animation class.
    - Color - A color class.
    - Ellipse - An ellipse shape class.
    - RoundedRectangle - A class for rectangles whose corners are rounded.
    - Squircle - A squircle class based on x^4 + y^4 = r^4 definition.
- **Managers:** Managers for various Game Development related objects.
    - AnimationManager - Manages animations for one sprite. Makes animations really easy to implement for SFML. Inherits from ManagerBase\<Animation\>
    - ManagerBase - Base manager class. All the other managers classes are derived from this class.
    - MusicManager - Simple music manager class that stores musics in a hashmap and can play them. Inherits from ManagerBase\<sf::Music\>
    - SceneManager - Simple scene manager class. Stores shared pointers to Scene objects. Inherits from ManagerBase\<std::shared_ptr\<Scene\>\>
    - SoundManager - Simple sound manager class that stores sounds and their buffers into seperate hashmaps. Inherits from ManagerBase\<sf::Sound\>
    - SpriteManager - Simple SpriteManager class. Inherits from ManagerBase\<sf::Sprite\>
    - TextureManager - Loads textures from various resources and stores them in a hashmap. Inherits from ManagerBase\<sf::Texture\>
- **Numeric:** Classes that are related to math.
    - Gradient - A gradient class that allows you to create gradients between anything that supports addition and multiplication operators.
    - Math - A math class that contains math constants and some functions that are not in c++ STL. Only contains static methods and constants so it doesn't meant to be instantiated.
    - Vector2 - 2D Vector class that adds some linear algebra functions and operators to sf::Vector2\<T\>
    - Vector3 - 3D Vector class that adds some linear algebra functions and operators to sf::Vector3\<T\>

# Building SFEX

To build SFEX from source, make sure that you have cmake and make installed. Then, open up a terminal and run these commands.
```bash
# Clone the git repository
git clone https://github.com/DolphyWind/SFML-Extended
# Change your directory
cd SFML-Extended
# Create build folder and move into it
mkdir build
cd build
# Run CMake to generate build files
cmake .. -DCMAKE_BUILD_TYPE=Release
# Alternatively, you can also enable BUILD_DOCS option in CMake to generate documentation via Doxygen.
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_DOCS=ON
# Run make to build SFEX
make
# Run tests (If BUILD_TESTS is set to ON)
ctest
# Install SFEX to your system
sudo make install
```
