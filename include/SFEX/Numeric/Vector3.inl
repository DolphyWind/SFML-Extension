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

// Headers
#include <SFEX/Numeric/Vector3.hpp>
#include <ostream>

namespace sfex
{

template<typename T>
Vector3<T>::Vector3(): x(T()), y(T()), z(T())
{
}

template<typename T>
Vector3<T>::Vector3(const sf::Vector3<T> &sfVec): x(sfVec.x), y(sfVec.y), z(sfVec.z)
{
}

template<typename T>
Vector3<T>::Vector3(const T &_x, const T &_y, const T &_z): x(_x), y(_y), z(_z) 
{
}

template<typename T>
float Vector3<T>::magnitude() const
{
    return std::sqrt(x*x + y*y + z*z);
}

template<typename T>
void Vector3<T>::setMagnitude(float magnitude)
{
    float mag = this->magnitude();
    x *= (magnitude / mag);
    y *= (magnitude / mag);
    z *= (magnitude / mag);
}

template<typename T>
void Vector3<T>::normalize()
{
    this->setMagnitude(1);
}

template<typename T>
Vector3<T> Vector3<T>::normalized() const
{
    Vector3<T> resultVector = *this;
    resultVector.normalize();
    return resultVector;
}

template<typename T>
T Vector3<T>::dot(const Vector3<T> &rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

template<typename T>
Vector3<T> Vector3<T>::cross(const Vector3<T> &rhs) const
{
    return {
        y * rhs.z - z * rhs.y,
        z * rhs.x - x * rhs.z,
        x * rhs.y - y * rhs.x,
    };
}

template<typename T>
Vector3<T> Vector3<T>::cwiseMul(const Vector3<T> &rhs) const
{
    return {x * rhs.x, y * rhs.y, z * rhs.z};
}

template<typename T>
Vector3<T> Vector3<T>::cwiseDiv(const Vector3<T> &rhs) const
{
    return {x / rhs.x, y / rhs.y, z / rhs.z};
}

template<typename T>
void Vector3<T>::scale(const T &scalar)
{
    *this = this->cwiseMul({scalar, scalar, scalar});
}

template<typename T>
Vector3<T> Vector3<T>::scaled(const T &scalar) const 
{
    Vector3<T> resultVector = *this;
    resultVector.scale(scalar);
    return resultVector;
}

template<typename T>
void Vector3<T>::rotate(float x_angle, float y_angle, float z_angle, const Vector3<T> &rotateAround)
{
    // To make computation faster
    float cos_alpha = std::cos(x_angle);
    float sin_alpha = std::sin(x_angle);
    float cos_beta = std::cos(y_angle);
    float sin_beta = std::sin(y_angle);
    float cos_gamma = std::cos(z_angle);
    float sin_gamma = std::sin(z_angle);

    *this -= rotateAround;

    // Where x goes
    T x_prime = T(
        (cos_beta * cos_gamma) * x +
        (sin_alpha * sin_beta * cos_gamma - cos_alpha * sin_gamma) * y +
        (cos_alpha * sin_beta * cos_gamma + sin_alpha * sin_gamma) * z
    );

    // Where y goes
    T y_prime = T(
        (cos_beta * sin_gamma) * x +
        (sin_alpha * sin_beta * sin_gamma + cos_alpha * cos_gamma) * y +
        (cos_alpha * sin_beta * sin_gamma - sin_alpha * cos_gamma) * z
    );

    // Where z goes
    T z_prime = T(
        (-sin_beta) * x +
        (sin_alpha * cos_beta) * y +
        (cos_alpha * cos_beta) * z
    );

    *this = Vector3<T>(x_prime, y_prime, z_prime) + rotateAround;
}

template<typename T>
Vector3<T> Vector3<T>::rotated(float x_angle, float y_angle, float z_angle, const Vector3<T> &rotateAround) const
{
    Vector3<T> resultVector = *this;
    resultVector.rotate(x_angle, y_angle, z_angle, rotateAround);
    return resultVector;
}

template<typename T>
float Vector3<T>::angle(const Vector3<T> &other) const
{
    return std::acos(this->dot(other) / (this->magnitude() * other.magnitude()));
}

template<typename T>
void Vector3<T>::projectOnto(const Vector3<T> &rhs)
{
    float magnitude_squared = rhs.magnitude() * rhs.magnitude();
    *this = rhs * this->dot(rhs)/magnitude_squared;
}

template<typename T>
void Vector3<T>::projectOntoPlane(float a, float b, float c)
{
    // A normal vector of a plane is the coefficents of x, y and z as a vector
    this->projectOntoPlane({a, b, c});
}

template<typename T>
void Vector3<T>::projectOntoPlane(const Vector3<T> &normal)
{
    Vector3<T> normal_porjected = this->projectedOnto(normal);
    *this -= normal_porjected;
}

template<typename T>
Vector3<T> Vector3<T>::projectedOnto(const Vector3<T> &rhs) const
{
    Vector3<T> resultVector = *this;
    resultVector.projectOnto(rhs);
    return resultVector;
}

template<typename T>
Vector3<T> Vector3<T>::projectedOntoPlane(float a, float b, float c) const
{
    Vector3<T> resultVector = *this;
    resultVector.projectOntoPlane(a, b, c);
    return resultVector;
}

template<typename T>
Vector3<T> Vector3<T>::projectedOntoPlane(const Vector3<T> &normal) const
{
    Vector3<T> resultVector = *this;
    resultVector.projectOntoPlane(normal);
    return resultVector;
}

//////////////////////////////////////////////////////////
// Logical operators
//////////////////////////////////////////////////////////

template<typename T>
bool Vector3<T>::operator==(const Vector3<T> &rhs) const
{
    return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
}

template<typename T>
bool Vector3<T>::operator!=(const Vector3<T> &rhs) const
{
    return !(*this == rhs);
}

//////////////////////////////////////////////////////////
// Addition
//////////////////////////////////////////////////////////

template<typename T>
Vector3<T> Vector3<T>::operator+=(const Vector3 &rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

template<typename T>
Vector3<T> Vector3<T>::operator+(const Vector3 &rhs) const
{
    Vector3<T> resultVector = *this;
    return (resultVector += rhs);
}

//////////////////////////////////////////////////////////
// Subtraction
//////////////////////////////////////////////////////////

template<typename T>
Vector3<T> Vector3<T>::operator-=(const Vector3 &rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

template<typename T>
Vector3<T> Vector3<T>::operator-(const Vector3 &rhs) const
{
    Vector3<T> resultVector = *this;
    return (resultVector -= rhs);
}

template<typename T>
Vector3<T> Vector3<T>::operator-() const
{
    Vector3<T> resultVector;
    resultVector.x = -x;
    resultVector.y = -y;
    resultVector.z = -z;
    return resultVector;
}

//////////////////////////////////////////////////////////
// Multiplication
//////////////////////////////////////////////////////////

template<typename T>
Vector3<T> Vector3<T>::operator*=(const T &scalar)
{
    this->scale(scalar);
    return *this;
}

template<typename T>
Vector3<T> Vector3<T>::operator*(const T &scalar) const
{
    Vector3<T> resultVector = *this;
    return (resultVector *= scalar);
}

template<typename T>
Vector3<T> operator*(const T &scalar, const Vector3<T> &vec)
{
    return vec.scaled(scalar);
}

//////////////////////////////////////////////////////////
// Division
//////////////////////////////////////////////////////////

template<typename T>
Vector3<T> Vector3<T>::operator/=(const T &scalar)
{
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    return *this;
}

template<typename T>
Vector3<T> Vector3<T>::operator/(const T &scalar) const
{
    Vector3<T> resultVector = *this;
    return (resultVector /= scalar);
}

//////////////////////////////////////////////////////////
// SFML Vector Conversion
//////////////////////////////////////////////////////////

template<typename T>
template<typename T2>
sf::Vector3<T2> Vector3<T>::toSFMLVector() const
{
    return sf::Vector3<T2>(T2(x), T2(y), T2(z));
}

template<typename T>
sf::Vector3f Vector3<T>::toVector3f() const
{
    return toSFMLVector<float>();
}

template<typename T>
sf::Vector3i Vector3<T>::toVector3i() const
{
    return toSFMLVector<int>();
}

template<typename T>
template<typename T2>
Vector3<T>::operator sf::Vector3<T2>() const
{
    return toSFMLVector<T2>();
}

template<typename T>
template<typename T2>
Vector3<T> Vector3<T>::operator=(const sf::Vector3<T2> &rhs)
{
    *this = {rhs.x, rhs.y, rhs.z};
    return *this;
}

//////////////////////////////////////////////////////////
// Ostream
//////////////////////////////////////////////////////////

template<typename T>
std::ostream &operator<<(std::ostream &left, const sfex::Vector3<T> &right)
{
    return left << "(x: " << right.x << ", y: " << right.y << ", z: " << right.z << ")";
}

//////////////////////////////////////////////////////////
// Static properties
//////////////////////////////////////////////////////////

template<typename T>
const Vector3<T> Vector3<T>::one = {1, 1, 1};
template<typename T>
const Vector3<T> Vector3<T>::zero = {0, 0, 0};
template<typename T>
const Vector3<T> Vector3<T>::up = {0, 1, 0};
template<typename T>
const Vector3<T> Vector3<T>::down = {0, -1, 0};
template<typename T>
const Vector3<T> Vector3<T>::left = {-1, 0, 0};
template<typename T>
const Vector3<T> Vector3<T>::right = {1, 0, 0};
template<typename T>
const Vector3<T> Vector3<T>::forward = {0, 0, 1};
template<typename T>
const Vector3<T> Vector3<T>::back = {0, 0, -1};

} // namespace sfex
