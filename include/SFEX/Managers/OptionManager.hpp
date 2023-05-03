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

#ifndef _SFEX_MANAGERS_OPTIONMANAGER_
#define _SFEX_MANAGERS_OPTIONMANAGER_

#include <SFEX/Managers/ManagerBase.hpp>
#include <cstring>
#include <memory>
#include <ostream>
#include <fstream>
#include <algorithm>

namespace sfex
{

/// @brief A class for holding different types of variables under the name of one.
class OptionValue
{
public:
    enum class DataType
    {
        INT,
        DOUBLE,
        BOOLEAN,
        STRING,
        NONE,
    };

    /// @brief Construct an empty OptionValue object.
    explicit OptionValue(DataType datatype=DataType::NONE);

    /// @brief Copy constructor for OptionValue
    /// @param other The value you want to copy from
    OptionValue(const OptionValue& other);

    /// @brief Move constructor for OptionValue
    /// @param other The value you want to move from
    OptionValue(OptionValue&& other);

    /// @brief Construct a new OptionValue object as integer
    /// @param int_val Integer value
    OptionValue(int int_val);

    /// @brief Construct a new OptionValue object as double
    /// @param double_val Double value
    OptionValue(double double_val);

    /// @brief Construct a new OptionValue object as std::string using a char pointer.
    /// @param charptr_val Char pointer value
    OptionValue(const char* charptr_val);

    /// @brief Construct a new OptionValue object as std::string
    /// @param string_val std::string value
    OptionValue(const std::string &string_val);

    /// @brief Construct a new OptionValue object as bool
    /// @param bool_val Boolean value
    OptionValue(bool bool_val);

    /// @brief Destroy the OptionValue object
    ~OptionValue();

    
    /// @brief Assign OptionValue to a integer
    /// @param int_val New integer value
    OptionValue& operator=(int int_val);

    /// @brief Assign OptionValue to a double
    /// @param int_val New double value
    OptionValue& operator=(double double_val);

    /// @brief Assign OptionValue to a bool
    /// @param int_val New bool value
    OptionValue& operator=(bool bool_val);

    /// @brief Assign OptionValue to a char pointer
    /// @param charptr_val Char pointer
    OptionValue& operator=(const char* charptr_val);

    /// @brief Assign OptionValue to a std::string
    /// @param int_val New std::string value
    OptionValue& operator=(const std::string &string_val);

    /// @brief Assign OptionValue to another OptionValue
    /// @param other Other OptionValue
    OptionValue& operator=(const OptionValue &other);

    /// @brief Reset the OptionValue with the given datatypes
    /// @param datatype New datatype
    OptionValue& reset(DataType datatype);

    /// @brief Convert OptionValue object to std::string
    /// @return Result of the conversion
    std::string to_string() const;

    /// @brief Get the datatype of OptionValue
    /// @return The datatype of OptionValue
    DataType get_datatype() const;

    /// @brief Get the datatype as std::string
    /// @return Datatype as std::string
    std::string get_datatype_as_string() const;

    /// @brief Convert string to datatype object
    /// @param str String to convert to DataType object
    /// @return String converted to DataType object
    static DataType string_to_datatype(const std::string &str);

    /// @brief Convert OprionValue object to int. 
    /// @return Get OptionValue as int. If the m_datatype is not DataType::INT 0 will be returned.
    int as_int() const;

    /// @brief Convert OprionValue object to int. 
    /// @return Get OptionValue as int. If the m_datatype is not DataType::INT 0 will be returned.
    operator int() const;

    /// @brief Convert OprionValue object to double. 
    /// @return Get OptionValue as doubke. If the m_datatype is not DataType::DOUBLE 0.0 will be returned.
    double as_double() const;

    /// @brief Convert OprionValue object to double. 
    /// @return Get OptionValue as doubke. If the m_datatype is not DataType::DOUBLE 0.0 will be returned.
    operator double() const;

    /// @brief Convert OprionValue object to bool. 
    /// @return Get OptionValue as bool. If the m_datatype is not DataType::BOOLEAN false will be returned.
    bool as_bool() const;

    /// @brief Convert OprionValue object to bool. 
    /// @return Get OptionValue as bool. If the m_datatype is not DataType::BOOLEAN false will be returned.
    operator bool() const;

    /// @brief Convert OprionValue object to std::string. 
    /// @return Get OptionValue as std::string. If the m_datatype is not DataType::STRING an empty string will be returned.
    std::string as_string() const;

    /// @brief Convert OprionValue object to std::string. 
    /// @return Get OptionValue as std::string. If the m_datatype is not DataType::STRING an empty string will be returned.
    operator std::string() const;

    /// @brief << operator for printing OptionValue to screen.
    friend std::ostream& operator<<(std::ostream &left, const OptionValue &right);

private:
    DataType m_datatype;
    std::unique_ptr<char[]> m_data;
    std::size_t m_size;

    void cleanup();
    void update_value(std::size_t new_size, void* new_data, const DataType &datatype);
};

/// @brief Option struct that stores value and the default value of an option
struct Option
{
    OptionValue value;
    const OptionValue default_value;

    void reset();
};

/// @brief OptionManager that stores Options in a hashmap
class OptionManager : public ManagerBase<Option>
{
public:
    /// @brief Updates an option of OptionManager. Inserts a new option if key is not present.
    /// @param key Key of the new option
    /// @param val New option
    void updateOption(const std::string &key, const OptionValue &val);

    /// @brief Adds a new option to OptionManager. Does nothing if key is already present.
    /// @param key Key of the new option
    /// @param val New option value
    /// @param default_val Default value of that option
    void addOption(const std::string &key, const OptionValue &val, const OptionValue &default_val);

    /// @brief Parses settings from given file
    /// @param filename Name of the file you want to parse.
    /// @param create_file_if_not_exists If set to true, OptionManager will try to create the file if file is not present
    /// @return True if loading data was successfull. False otherwise
    bool parseFromFile(const std::string &filename, bool create_file_if_not_exists=false);

    /// @brief Save settings to specified file
    /// @param filename Name of the file you want to save to.
    /// @return True if saving data was successfull. False otherwise
    bool saveToFile(const std::string &filename);
private:
};

}

#endif //!_SFEX_MANAGERS_OPTIONMANAGER_