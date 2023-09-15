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
#include <sstream>
#include <unordered_map>
#include <optional>
#include <type_traits>

namespace impl
{
    // https://stackoverflow.com/questions/16337610/how-to-know-if-a-type-is-a-specialization-of-stdvector by Databyte
    template<typename Type, template<typename...> class Ref>
    struct is_specialization : std::false_type {};

    template<template<typename...> class Ref, typename... Args>
    struct is_specialization<Ref<Args...>, Ref>: std::true_type {};
}

namespace sfex
{

class Multitype;
typedef std::unordered_map<std::string, sfex::Multitype> MultitypeMap;

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
        MAP,
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

    /// @brief Construct a new Multitype object as a list
    /// @param vec_val A vector containing multitype values
    Multitype(const std::vector<Multitype> &vec_val);

    /// @brief Construct a new Multitype object as a list of integers
    /// @param int_vector A vector containing integers
    Multitype(const std::vector<int>& int_vector);

    /// @brief Construct a new Multitype object as a list of doubles
    /// @param double_vector A vector containing doubles
    Multitype(const std::vector<double>& double_vector);

    /// @brief Construct a new Multitype object as a list of booleans
    /// @param bool_vector A vector containing booleans
    Multitype(const std::vector<bool>& bool_vector);

    /// @brief Construct a new Multitype object as a list of strings
    /// @param string_vector A vector containing strings
    Multitype(const std::vector<std::string>& string_vector);

    /// @brief Construct a new Multitype object as a list
    /// @param list_val Initializer list containing Multitype objects
    Multitype(const std::initializer_list<Multitype> &list_val);

    /// @brief Construct a new Multitype object as a map
    /// @param map_val Map value
    Multitype(const MultitypeMap &map_val);

    /// @brief Construct a new Multitype object as a map
    /// @param map_val Map value
    template<typename T>
    Multitype(const std::unordered_map<std::string, T>& map_val);

    /// @brief Construct a new Multitype object as a map
    /// @param pair_list_val Pair Initializer list
    Multitype(const std::initializer_list<std::pair<std::string, Multitype>> &pair_list_val);

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

    /////////////////////////////////////////
    /// BRACKET OPERATORS
    /////////////////////////////////////////

    /// @brief Interpret the multitype object as a list and get an element from it.
    /// @param index Index of the element to get
    /// @return The element with the given index
    const sfex::Multitype operator[](std::size_t index);

    /// @brief Interpret the multitype object as a map and get an element from it
    /// @param key Key of the element to get
    /// @return The element that corresponds to the given key
    const sfex::Multitype operator[](const std::string& key);

    /// @brief Interpret the multitype object as a map and get an element from it
    /// @param key Key of the element to get
    /// @return The element that corresponds to the given key
    const sfex::Multitype operator[](const char* key);

    /////////////////////////////////////////
    /// FUNCTIONALITIES
    /////////////////////////////////////////

    /// @brief Reset the Multitype with the given datatype
    /// @param datatype New datatype
    Multitype& reset(DataType datatype);

    /// @brief Convert the Multitype object to std::string
    /// @return Result of the conversion
    std::string to_string() const;

    /// @brief Serialize the Multitype object into std::string
    /// @return Result of the serialization
    std::string serialize(bool prettify=false) const;

    /// @brief Get the datatype of the Multitype object
    /// @return The datatype of Multitype object
    DataType get_datatype() const;

    /// @brief Get the datatype as a std::string
    /// @return Datatype as a std::string
    std::string get_datatype_as_string() const;

    /// @brief Convert string to datatype object
    /// @param str String to convert to DataType object
    /// @return String converted to DataType object
    static DataType string_to_datatype(const std::string &str);

    /// @brief Convert given type to a datatype object
    /// @tparam T Type to convert
    /// @return The type converted to a datatype object. DataType::NONE is returned if type is not supported.
    template<typename T>
    static DataType typeToDatatype();

    /// @brief Parses a string to a Multitype
    /// @param str String to parse
    /// @return Result of parsing
    /// @throws std::runtime_error on parse errors, std::invalid_argument on empty string
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

    /// @brief Convert Multitye object to std::vector<T>
    /// @return Get Multitype as std::vector<T>. If the m_datatype is not DataType::LIST an empty vector will be returned.
    template<typename T>
    std::vector<T> as_list() const;

    /// @brief Convert Multitype object to std::vector<Multitype>
    /// @return Get Multitype as std::vector<Multitype>. If the m_datatype is not DataType::LIST an empty vector will be returned.
    operator std::vector<Multitype>() const;

    /// @brief Convert Multitype object to std::unordered_map<std::string, Multitype>
    /// @return Get Multitype as std::unordered_map<std::string, Multitype>. If the m_datatype is not DataType::MAP an empty map will be returned.
    MultitypeMap as_map() const;

    /// @brief Covert Multitype object to std::unordered_map<std::string, T>
    /// @return Get Multitype as std::unordered_map<std::string, T>. If the m_datatype is not DataType::MAP an empty map will be returned.
    template<typename T>
    std::unordered_map<std::string, T> as_map() const;

    /// @brief Convert Multitype object to std::unordered_map<std::string, Multitype>
    /// @return Get Multitype as std::unordered_map<std::string, Multitype>. If the m_datatype is not DataType::MAP an empty map will be returned.
    operator MultitypeMap() const;

    /// @brief << operator for printing Multitype to an ostream.
    friend std::ostream& operator<<(std::ostream &left, const Multitype &right);

    static const Multitype null;

private:
    DataType m_datatype;
    std::unique_ptr<char[]> m_data;
    std::size_t m_size;

    void cleanup();
    void update_value(std::size_t new_size, void* new_data, const DataType &datatype);
    std::string to_string_priv(bool serialize=false, bool prettify=false, std::size_t indent=0, bool special_prettify=false) const;
};

template<typename T>
Multitype::Multitype(const std::unordered_map<std::string, T>& map_val): m_datatype(DataType::MAP), m_data(nullptr), m_size((sizeof(Multitype)+sizeof(char*))*map_val.size())
{
    struct Pair
    {
        std::unique_ptr<char[]> char_ptr;
        Multitype multitype;
    };

    std::unique_ptr<Pair[]> values = std::make_unique<Pair[]>(map_val.size());
    
    std::size_t i = 0;
    for(auto&[key, value] : map_val)
    {
        Pair p;
        p.char_ptr = std::make_unique<char[]>(0);
        std::memcpy(p.char_ptr.get(), key.c_str(), key.length()+1);
        p.multitype = value;
        *(values.get() + i) = std::move(p);
        i++;
    }
    update_value(m_size, values.release(), m_datatype);
}

template<typename T>
Multitype::DataType Multitype::typeToDatatype()
{
    if constexpr(std::is_same<bool, T>::value) return DataType::BOOLEAN;
    if constexpr(std::is_integral<T>::value) return DataType::INT;
    if constexpr(std::is_floating_point<T>::value) return DataType::DOUBLE;
    if constexpr(std::is_same<T, std::string>::value || 
                 std::is_same<T, std::wstring>::value ||
                 std::is_same<T, std::u16string>::value ||
                 std::is_same<T, std::u32string>::value ||
                 std::is_same<T, char**>::value
    ) return DataType::STRING;
    if constexpr(impl::is_specialization<T, std::unordered_map>::value) return DataType::MAP;
    if constexpr(impl::is_specialization<T, std::vector>::value) return DataType::LIST;

    return DataType::NONE;
}

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

template<typename T>
std::vector<T> Multitype::as_list() const
{
    std::vector<Multitype> this_as_list = this->as_list();

    DataType targetType = Multitype::typeToDatatype<T>();
    std::vector<T> resultVector;
    resultVector.reserve(this_as_list.size());

    for(auto& item : this_as_list)
    {
        resultVector.push_back((T)item);
    }

    return resultVector;
}

template<typename T>
std::unordered_map<std::string, T> Multitype::as_map() const
{
    MultitypeMap this_as_map = this->as_map();

    DataType targetType = Multitype::typeToDatatype<T>();
    std::unordered_map<std::string, T> resultMap;
    resultMap.reserve(this_as_map.size());

    for(auto&[key, value] : this_as_map)
    {
        resultMap[key] = (T)value;
    }

    return resultMap;
}

}

#endif  // !_SFEX_GENERAL_MULTITYPE_HPP_