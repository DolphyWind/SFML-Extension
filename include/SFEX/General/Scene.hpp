//
// MIT License
//
// Copyright (c) 2023 Yunus Emre Aydın
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifndef _SFEX_GENERAL_SCENE_HPP_
#define _SFEX_GENERAL_SCENE_HPP_

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace sfex
{

/// @brief Base scene class. Functions do what their descriotions say when a child class is used with a sfex::SceneManager object.
class Scene
{
public:
    /// @brief Event hadling function for a scene
    /// @param e Event to handle
    virtual void pollEvent(const sf::Event &e) {};
    
    /// @brief Start function runs once when the scene is loaded.
    virtual void start() {};

    /// @brief Update function is for updating the scene.
    virtual void update() {};

    /// @brief Draw function draws the scene drawables to a target
    /// @param target Target to draw onto
    virtual void draw(sf::RenderTarget &target) {};

    /// @brief Destroy functiun runs when a scene manager switchs to a new scene.
    virtual void destroy() {};
};

} // namespace sfex


#endif // !_SFEX_GENERAL_SCENE_HPP_