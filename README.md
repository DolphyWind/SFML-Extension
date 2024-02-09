**THIS LIBRARY IS WORK IN PROGRESS. ANY FEATURE CAN CHANGE IN ANYTIME.**

# SFEX - SFML Extension
SFML Extension is a set of classes/functions to speed up SFML Game development.

# Build Status
[![Linux Build](https://github.com/DolphyWind/SFML-Extension/actions/workflows/linux_build.yml/badge.svg)](https://github.com/DolphyWind/SFML-Extension/actions/workflows/linux_build.yml)  
[![Windows Build](https://github.com/DolphyWind/SFML-Extension/actions/workflows/windows_build.yml/badge.svg)](https://github.com/DolphyWind/SFML-Extension/actions/workflows/windows_build.yml)  
[![MacOS build](https://github.com/DolphyWind/SFML-Extension/actions/workflows/mac_build.yml/badge.svg)](https://github.com/DolphyWind/SFML-Extension/actions/workflows/mac_build.yml)  
[![Building Documentation](https://github.com/DolphyWind/SFML-Extension/actions/workflows/build_docs.yml/badge.svg)](https://github.com/DolphyWind/SFML-Extension/actions/workflows/build_docs.yml)

# What This Library Provides
SFEX currently contains 4 modules: General, Graphics, Managers and Numeric.

- **General:** Classes that doesn't fit into other modules.
    - Joystick - Simple joystick class for detecting and proccessing the joystick input. Only contains static methods.
    - Keyboard - Simple keyboard class for detecting and proccessing the keyboard input. Only contains static methods.
    - Listener - Listener class that can be instantiated unlike sf::Listener.
    - Mouse - Simple mouse class for detecting and proccessing the mouse input. Only contains static methods.
    - Multitype - A class for holding different types of variables under the name of one.
    - Scene - Base scene class.
    - Singleton - A singleton base class. 
    - StaticClass - A base class for static classes like sfex::Joystick, sfex::Keyboard, sfex::Mouse, sfex::Math.
    - Stopwatch - Measures the elapsed time. Can be paused and resumed.
- **Graphics:** Classes that are related to graphics.
    - Animation - A class for sprite sheet animations.
    - Color - A color class.
    - Ellipse - An ellipse shape class.
    - RoundedRectangle - A class for rectangles with smoothed out corners.
    - Squircle - A squircle shape class based on x^4 + y^4 = r^4 definition.
    - Star - A star shape class.
- **Managers:** Managers for various Game Development related objects.
    - AnimationManager - Manages animations for one sprite. Makes animations really easy to implement for SFML. Inherits from `ManagerBase<Animation>`
    - ManagerBase - Base manager class. All the other managers classes are derived from this class.
    - MusicManager - Simple music manager class that stores musics in a hashmap and can play them. Inherits from `ManagerBase<sf::Music>`
    - OptionManager - Simple OptionManager that stores Options in a hashmap. It also support JSON format. Inherits from `ManagerBase<sfex::Option>`
    - SceneManager - Simple scene manager class. Stores shared pointers to Scene objects. Inherits from `ManagerBase<std::shared_ptr<Scene>>`
    - SoundManager - Simple sound manager class that stores sounds and their buffers into seperate hashmaps. Inherits from `ManagerBase<sf::Sound>`
    - SpriteManager - Simple SpriteManager class. Inherits from `ManagerBase<sf::Sprite>`
    - TextureManager - Loads textures from various resources and stores them in a hashmap. Inherits from `ManagerBase<sf::Texture>`
- **Numeric:** Classes that are related to math.
    - AngleSystem - A class for representing angle measurement systems.
    - Gradient - A gradient class that allows you to create gradients between anything that supports addition and multiplication operators.
    - Math - A math class that contains some math constants and functions. Only contains static methods and constants so it doesn't meant to be instantiated.
    - `Vector<N, T>` - N-Dimensional Vector class.
    - `Vector2<T>` - 2D Vector class that adds some linear algebra functions and operators to `sf::Vector2<T>`
    - `Vector3<T>` - 3D Vector class that adds some linear algebra functions and operators to `sf::Vector3<T>`

# Building SFEX

To build SFEX from source, make sure that you have cmake and make installed. Then, open up a terminal and run these commands.
```bash
# Clone the git repository
git clone https://github.com/DolphyWind/SFML-Extension
# Change your directory
cd SFML-Extension
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
