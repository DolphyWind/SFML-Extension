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

#ifndef _SFEX_GENERAL_MULTITYPE_HPP_
#define _SFEX_GENERAL_MULTITYPE_HPP_
#include <string>
#include <cstring>
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <iostream>

namespace sfex
{

/// @brief A class for holding different types of variables under the name of one.
class Multitype
{
public:
    enum class DataType
    {
        INT,
        DOUBLE,
        BOOLEAN,
        STRING,
        LIST,
        NONE,
    };

    /// @brief Construct an empty Multitype object.
    explicit Multitype(DataType datatype=DataType::NONE);

    /// @brief Copy constructor for Multitype
    /// @param other The value you want to copy from
    Multitype(const Multitype& other);

    /// @brief Move constructor for Multitype
    /// @param other The value you want to move from
    Multitype(Multitype&& other);

    /// @brief Construct a new Multitype object as integer
    /// @param int_val Integer value
    Multitype(int int_val);

    /// @brief Construct a new Multitype object as double
    /// @param double_val Double value
    Multitype(double double_val);

    /// @brief Construct a new Multitype object as std::string using a char pointer.
    /// @param charptr_val Char pointer value
    Multitype(const char* charptr_val);

    /// @brief Construct a new Multitype object as std::string
    /// @param string_val std::string value
    Multitype(const std::string &string_val);

    /// @brief Construct a new Multitype object as bool
    /// @param bool_val Boolean value
    Multitype(bool bool_val);

    /// @brief Construct a new Option Value object as a vector
    /// @param vec_val Vector value
    Multitype(const std::vector<Multitype> &vec_val);

    /// @brief Destroy the Multitype object
    ~Multitype();

    /////////////////////////////////////////
    /// LOGICAL OPERATORS
    /////////////////////////////////////////
    
    /// @brief Checks if the given Multitype is equals to this Multitype. Returns false if the datatypes does not match.
    /// @param other Other Multitype
    /// @return Result of comparison
    bool operator==(const Multitype &other) const;
    
    /// @brief Checks if the given Multitype is equals to this Multitype. Returns false if the datatypes does not match.
    /// @param other Other value
    /// @return Result of comparison
    template<typename T>
    bool operator==(const T &other) const;

    /// @brief Checks if the given Multitype is not equals to this Multitype. Returns true if the datatypes does not match.
    /// @param other Other Multitype
    /// @return Result of the comparison.
    bool operator!=(const Multitype &other) const;

    /// @brief Checks if the given Multitype is not equals to this Multitype. Returns true if the datatypes does not match.
    /// @param other Other value
    /// @return Result of the comparison.
    template<typename T>
    bool operator!=(const T &other) const;

    /// @brief Checks if the this Multitype is less than other Multitype.
    /// @param other Other Multitype
    /// @throws std::runtime_error if datatypes does not match or values are not comparable with less than operator.
    /// @return Result of the comparison.
    bool operator<(const Multitype &other) const;

    /// @brief Checks if the this Multitype is less than other Multitype.
    /// @param other Other value
    /// @throws std::runtime_error if datatypes does not match or values are not comparable with less than operator.
    /// @return Result of the comparison.
    template<typename T>
    bool operator<(const T &other) const;

    /// @brief Checks if the this Multitype is greater than other Multitype.
    /// @param other Other Multitype
    /// @throws std::runtime_error if datatypes does not match or values are not comparable with less than operator.
    /// @return Result of the comparison.
    bool operator>(const Multitype &other) const;

    /// @brief Checks if the this Multitype is greater than other Multitype.
    /// @param other Other value
    /// @throws std::runtime_error if datatypes does not match or values are not comparable with less than operator.
    /// @return Result of the comparison.
    template<typename T>
    bool operator>(const T &other) const;

    /// @brief Checks if the this Multitype is less than or equals to other Multitype.
    /// @param other Other Multitype
    /// @throws std::runtime_error if datatypes does not match or values are not comparable with less than operator.
    /// @return Result of the comparison.
    bool operator<=(const Multitype &other) const;

    /// @brief Checks if the this Multitype is less than or equals to other Multitype.
    /// @param other Other value
    /// @throws std::runtime_error if datatypes does not match or values are not comparable with less than operator.
    /// @return Result of the comparison.
    template<typename T>
    bool operator<=(const T &other) const;

    /// @brief Checks if the this Multitype is greater than or equals to other Multitype.
    /// @param other Other Multitype
    /// @throws std::runtime_error if datatypes does not match or values are not comparable with less than operator.
    /// @return Result of the comparison.
    bool operator>=(const Multitype &other) const;

    /// @brief Checks if the this Multitype is greater than or equals to other Multitype.
    /// @param other Other value
    /// @throws std::runtime_error if datatypes does not match or values are not comparable with less than operator.
    /// @return Result of the comparison.
    template<typename T>
    bool operator>=(const T &other) const;

    /////////////////////////////////////////
    /// ARITHMETICAL OPERATORS
    /////////////////////////////////////////

    /// @brief Adds two Multitypes, modifies this value and returns it.
    /// @param other Other Multitype
    /// @throws std::runtime_error if datatypes does not match or the values are not addable.
    /// @return this Multitype
    Multitype& operator+=(const Multitype &other);

    /// @brief Adds two Multitypes, modifies this value and returns it.
    /// @param other Other value
    /// @throws std::runtime_error if datatypes does not match or the values are not addable.
    /// @return this Multitype
    template<typename T>
    Multitype& operator+=(const T &other);

    /// @brief Adds two Multitypes and returns it.
    /// @param other Other Multitype
    /// @throws std::runtime_error if datatypes does not match or the values are not addable.
    /// @return this Multitype
    Multitype operator+(const Multitype &other) const;

    /// @brief Adds two Multitypes and returns it.
    /// @param other Other value
    /// @throws std::runtime_error if datatypes does not match or the values are not addable.
    /// @return this Multitype
    template<typename T>
    Multitype operator+(const T &other) const;

    /// @brief Subtracts two Multitypes, modifies this value and returns it.
    /// @param other Other Multitype
    /// @throws std::runtime_error if datatypes does not match or the values are not subtractable.
    /// @return this Multitype
    Multitype& operator-=(const Multitype &other);

    /// @brief Subtracts two Multitypes, modifies this value and returns it.
    /// @param other Other value
    /// @throws std::runtime_error if datatypes does not match or the values are not subtractable.
    /// @return this Multitype
    template<typename T>
    Multitype& operator-=(const T &other);

    /// @brief Subtracts two Multitypes and returns it. 
    /// @param other Other Multitype
    /// @throws std::runtime_error if datatypes does not match or the values are not subtractable.
    /// @return this Multitype
    Multitype operator-(const Multitype &other) const;

    /// @brief Subtracts two Multitypes and returns it. 
    /// @param other Other value
    /// @throws std::runtime_error if datatypes does not match or the values are not subtractable.
    /// @return this Multitype
    template<typename T>
    Multitype operator-(const T &other) const;

    /// @brief Multiplies two Multitypes, modifies this value and returns it.
    /// @param other Other Multitype
    /// @throws std::runtime_error if datatypes does not match or the values are not multipliable.
    /// @return this Multitype
    Multitype& operator*=(const Multitype &other);

    /// @brief Multiplies two Multitypes, modifies this value and returns it.
    /// @param other Other value
    /// @throws std::runtime_error if datatypes does not match or the values are not multipliable.
    /// @return this Multitype
    template<typename T>
    Multitype& operator*=(const T &other);

    /// @brief Multiplies two Multitypes and returns it. 
    /// @param other Other Multitype
    /// @throws std::runtime_error if datatypes does not match or the values are not multipliable.
    /// @return this Multitype
    Multitype operator*(const Multitype &other) const;

    /// @brief Multiplies two Multitypes and returns it. 
    /// @param other Other value
    /// @throws std::runtime_error if datatypes does not match or the values are not multipliable.
    /// @return this Multitype
    template<typename T>
    Multitype operator*(const T &other) const;

    /// @brief Divides two Multitypes, modifies this value and returns it.
    /// @param other Other Multitype
    /// @throws std::runtime_error if datatypes does not match or the values are not dividable.
    /// @return this Multitype
    Multitype& operator/=(const Multitype &other);
    
    /// @brief Divides two Multitypes, modifies this value and returns it.
    /// @param other Other value
    /// @throws std::runtime_error if datatypes does not match or the values are not dividable.
    /// @return this Multitype
    template<typename T>
    Multitype& operator/=(const T &other);

    /// @brief Divides two Multitypes and returns it. 
    /// @param other Other Multitype
    /// @throws std::runtime_error if datatypes does not match or the given values are not dividable.
    /// @return this Multitype
    Multitype operator/(const Multitype &other) const;

    /// @brief Divides two Multitypes and returns it. 
    /// @param other Other value
    /// @throws std::runtime_error if datatypes does not match or the values are not dividable.
    /// @return this Multitype
    template<typename T>
    Multitype operator/(const T &other) const;

    /// @brief Assign Multitype to another Multitype
    /// @param other Other Multitype
    Multitype& operator=(const Multitype &other);

    /// @brief Assign Multitype to another value
    /// @param other Other Multitype
    template<typename T>
    Multitype& operator=(const T &other);

    /// @brief Reset the Multitype with the given datatypes
    /// @param datatype New datatype
    Multitype& reset(DataType datatype);

    /// @brief Convert Multitype object to std::string
    /// @return Result of the conversion
    std::string to_string() const;

    /// @brief Get the datatype of Multitype
    /// @return The datatype of Multitype
    DataType get_datatype() const;

    /// @brief Get the datatype as std::string
    /// @return Datatype as std::string
    std::string get_datatype_as_string() const;

    /// @brief Convert string to datatype object
    /// @param str String to convert to DataType object
    /// @return String converted to DataType object
    static DataType string_to_datatype(const std::string &str);

    /// @brief Parses a string to a Multitype
    /// @param str String to parse
    /// @return Result of parsing
    static Multitype parse(const std::string &str);
    
    /// @brief Convert Multitype object to int. 
    /// @return Get Multitype as int. If the m_values are not DataType::INT 0 will be returned.
    int as_int() const;

    /// @brief Convert Multitype object to int. 
    /// @return Get Multitype as int. If the m_datatype is not DataType::INT 0 will be returned.
    operator int() const;

    /// @brief Convert Multitype object to double. 
    /// @return Get Multitype as doubke. If the m_datatype is not DataType::DOUBLE 0.0 will be returned.
    double as_double() const;

    /// @brief Convert Multitype object to double. 
    /// @return Get Multitype as doubke. If the m_datatype is not DataType::DOUBLE 0.0 will be returned.
    operator double() const;

    /// @brief Convert Multitype object to bool. 
    /// @return Get Multitype as bool. If the m_datatype is not DataType::BOOLEAN false will be returned.
    bool as_bool() const;

    /// @brief Convert Multitype object to bool. 
    /// @return Get Multitype as bool. If the m_datatype is not DataType::BOOLEAN false will be returned.
    operator bool() const;

    /// @brief Convert Multitype object to std::string. 
    /// @return Get Multitype as std::string. If the m_datatype is not DataType::STRING an empty string will be returned.
    std::string as_string() const;

    /// @brief Convert Multitype object to std::string. 
    /// @return Get Multitype as std::string. If the m_datatype is not DataType::STRING an empty string will be returned.
    operator std::string() const;

    /// @brief Convert Multitype object to std::vector<Multitype>
    /// @return Get Multitype as std::vector<Multitype>. If the m_datatype is not DataType::LIST an empty vector will be returned.
    std::vector<Multitype> as_list() const;

    /// @brief Convert Multitype object to std::vector<Multitype>
    /// @return Get Multitype as std::vector<Multitype>. If the m_datatype is not DataType::LIST an empty vector will be returned.
    operator std::vector<Multitype>() const;

    /// @brief << operator for printing Multitype to screen.
    friend std::ostream& operator<<(std::ostream &left, const Multitype &right);

    static const Multitype null;

private:
    DataType m_datatype;
    std::unique_ptr<char[]> m_data;
    std::size_t m_size;

    void cleanup();
    void update_value(std::size_t new_size, void* new_data, const DataType &datatype);
};

template<typename T>
bool Multitype::operator==(const T &other) const
{
    return (*this == Multitype(other));
}

template<typename T>
bool Multitype::operator!=(const T &other) const
{
    return (*this != Multitype(other));
}

template<typename T>
bool Multitype::operator<(const T &other) const
{
    return (*this < Multitype(other));
}

template<typename T>
bool Multitype::operator>(const T &other) const
{
    return (*this > Multitype(other));
}

template<typename T>
bool Multitype::operator<=(const T &other) const
{
    return (*this <= Multitype(other));
}

template<typename T>
bool Multitype::operator>=(const T &other) const
{
    return (*this >= Multitype(other));
}

template<typename T>
Multitype& Multitype::operator+=(const T &other)
{
    return (*this += Multitype(other));
}

template<typename T>
Multitype Multitype::operator+(const T &other) const
{
    return (*this + Multitype(other));
}

template<typename T>
Multitype& Multitype::operator-=(const T &other)
{
    return (*this -= Multitype(other));
}

template<typename T>
Multitype Multitype::operator-(const T &other) const
{
    return (*this - Multitype(other));
}

template<typename T>
Multitype& Multitype::operator*=(const T &other)
{
    return (*this *= Multitype(other));
}

template<typename T>
Multitype Multitype::operator*(const T &other) const
{
    return (*this * Multitype(other));
}

template<typename T>
Multitype& Multitype::operator/=(const T &other)
{
    return (*this /= Multitype(other));
}

template<typename T>
Multitype Multitype::operator/(const T &other) const
{
    return (*this / Multitype(other));
}

template<typename T>
Multitype& Multitype::operator=(const T &other)
{
    return (*this = Multitype(other));
}


}

#endif  // !_SFEX_GENERAL_MULTITYPE_HPP_