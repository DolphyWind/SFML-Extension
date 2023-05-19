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

#ifndef _SFEX_NUMERIC_VECTOR3_HPP_
#define _SFEX_NUMERIC_VECTOR3_HPP_

// Headers
#include <array>
#include <cmath>
#include <SFML/System/Vector3.hpp>
#include <SFEX/Numeric/Math.hpp>
#include <ostream>

namespace sfex
{

/// @brief 3D Vector class that adds some linear algebra functions and operators to sf::Vector3<T>
template<typename T>
class Vector3 : public sf::Vector3<T>
{
public:

    /// @brief Default constructor. Creates a zero vector.
    Vector3();

    /// @brief Creates a sfex::Vector3<T> from SFML vector
    /// @param sfVec SFML vector
    Vector3(const sf::Vector3<T> &sfVec);
    
    /// @brief Creates a vector with components x, y and z
    Vector3(const T &x, const T &y, const T &z);

    /// @brief Returns magnitude (length) of the vector
    /// @return Magnitude of the vector
    float magnitude() const;
    
    /// @brief Returns the magnitude (length) of the vector squared. Use this to avoid sqrt operation when magnitude squared gets the job done.
    /// @return Magnitude squared.
    float magnitude2() const;

    /// @brief Changes the vector's magnitude while keeping its direction same
    /// @param magnitude Target magnitude
    void setMagnitude(float magnitude);

    /// @brief Sets the vector's length to 1. Shorthand for setMagnitude(1) 
    void normalize();

    /// @brief Returns the normalized version of the vector
    /// @return Normalized version of vector
    Vector3<T> normalized() const;

    /// @brief Computates the dot product between this and rhs 
    /// @param rhs rhs vector
    /// @return Result of this . rhs
    T dot(const Vector3<T> &rhs) const;

    /// @brief Computates cross product between this and rhs
    /// @param rhs rhs vector
    /// @return Result of this x rhs
    Vector3<T> cross(const Vector3<T> &rhs) const;

    /// @brief Computates component-wise product aka hadamard product between two vectors
    /// @param rhs rhs vector
    /// @return Result of component-wise multiplication.
    Vector3<T> cwiseMul(const Vector3<T> &rhs) const;

    /// @brief Computates component-wise division aka hadamard division between two vectors
    /// @param rhs rhs vector
    /// @return Result of component-wise division.
    Vector3<T> cwiseDiv(const Vector3<T> &rhs) const;

    /// @brief Scales the vector with a scalar
    /// @param scalar scalar
    void scale(const T &scalar);

    /// @brief Returns a scaled version of the vector
    /// @param scalar scalar
    /// @return Scaled version of the vector
    Vector3<T> scaled(const T &scalar) const;

    /// @brief Rotates the vector around "rotateAround" by given Euler angles.
    /// @param x_angle rotation in x axis (Euler angles)
    /// @param y_angle rotation in y axis (Euler angles)
    /// @param z_angle rotation in z axis (Euler angles)
    /// @param rotateAround rotateAround vector (Defaults to Vector3<T>::zero)
    void rotate(float x_angle, float y_angle, float z_angle, const Vector3<T> &rotateAround = Vector3<T>::zero);

    /// TODO: Add quarternion rotation and quarternion class

    /// @brief Returns Rotated version of the vector around "rotateAround" vector.
    /// @param x_angle rotation in x axis (Euler angles)
    /// @param y_angle rotation in y axis (Euler angles)
    /// @param z_angle rotation in z axis (Euler angles)
    /// @param rotateAround rotateAround vector (Defaults to Vector3<T>::zero)
    /// @return Rotated version of vector
    Vector3<T> rotated(float x_angle, float y_angle, float z_angle, const Vector3<T> &rotateAround = Vector3<T>::zero) const;

    /// @brief Computates the angle between the vector and "other" vector. 
    /// @param other other vector.
    /// @return Angle between the vector and "other" as radians
    float angle(const Vector3<T> &other) const;

    /// @brief Projects this vector onto rhs vector
    /// @param rhs rhs vector
    void projectOnto(const Vector3<T> &rhs);

    /// @brief Projects this vector onto plane ax + by + cz = 0
    /// @param a coefficent of x
    /// @param b coefficent of y
    /// @param c coefficent of z
    void projectOntoPlane(float a, float b, float c);

    /// @brief Projects this vector onto plane by given point and normal vector
    /// @param normal normal vector of the plane
    void projectOntoPlane(const Vector3<T> &normal);

    /// @brief Returns projected version of this vector onto rhs vector
    /// @param rhs rhs vector
    /// @return Projected vector
    Vector3<T> projectedOnto(const Vector3<T> &rhs) const;

    /// @brief Returns projected version of this vector onto plane ax + by + cz = 0
    /// @param a coefficent of x
    /// @param b coefficent of y
    /// @param c coefficent of z
    Vector3<T> projectedOntoPlane(float a, float b, float c) const;

    /// @brief Returns projected version of this vector onto plane given a normal vector
    /// @param normal normal vector of the plane
    Vector3<T> projectedOntoPlane(const Vector3<T> &normal) const;

    bool operator==(const Vector3<T> &rhs) const;
    bool operator!=(const Vector3<T> &rhs) const;

    Vector3<T> operator+=(const Vector3<T> &rhs);
    Vector3<T> operator+(const Vector3<T> &rhs) const;

    Vector3<T> operator-=(const Vector3<T> &rhs);
    Vector3<T> operator-(const Vector3<T> &rhs) const;
    Vector3<T> operator-() const;

    Vector3<T> operator*=(const T &scalar);
    Vector3<T> operator*(const T &scalar) const;

    Vector3<T> operator/=(const T &scalar);
    Vector3<T> operator/(const T &scalar) const;

    /// @brief Converts sfex::Vector3<T> to sf::Vector3<T>
    /// @return Vector converted to sf::Vector3<T2>
    template<typename T2>
    sf::Vector3<T2> toSFMLVector() const;

    /// @brief Converts sfex::Vector3<T> to sf::Vector3f
    /// @return Vector converted to sf::Vector3f
    sf::Vector3f toVector3f() const;

    /// @brief Converts sfex::Vector3<T> to sf::Vector3i
    /// @return Vector converted to sf::Vector3i
    sf::Vector3i toVector3i() const;
    
    template<typename T2>
    operator sf::Vector3<T2>() const;
    
    template<typename T2>
    Vector3<T> operator=(const sf::Vector3<T2> &rhs);

    /// @brief Vector <1, 1, 1>
    static const Vector3<T> one;

    /// @brief Vector <0, 0, 0>
    static const Vector3<T> zero;

    /// @brief Vector <0, 1, 0>
    static const Vector3<T> up;

    /// @brief Vector <0, -1, 0>
    static const Vector3<T> down;

    /// @brief Vector <1, 0, 0>
    static const Vector3<T> right;

    /// @brief Vector <-1, 0, 0>
    static const Vector3<T> left;

    /// @brief Vector <0, 0 1>
    static const Vector3<T> forward;

    /// @brief Vector <0, 0 -1>
    static const Vector3<T> back;
};

typedef Vector3<float> Vec3;
typedef Vector3<int> Vec3i;
typedef Vector3<unsigned int> Vec3u;

template<typename T>
sfex::Vector3<T> operator*(const T &scalar, const sfex::Vector3<T> &vec);

template<typename T>
std::ostream &operator<<(std::ostream &left, const sfex::Vector3<T> &right);

} // namespace sfex

#include <SFEX/Numeric/Vector3.inl>

#endif // !_SFEX_NUMERIC_VECTOR3_HPP_