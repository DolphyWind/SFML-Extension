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

#ifndef _SFEX_MANAGERS_SETTINGSMANAGER_
#define _SFEX_MANAGERS_SETTINGSMANAGER_

#include <SFEX/Managers/ManagerBase.hpp>
#include <variant>

namespace sfex
{

/// @brief A class for holding different type of variables.
class OptionValue
{
public:
    enum class DataType
    {
        INT,
        DOUBLE,
        BOOLEAN,
        STRING,
        OTHER,
    };

    /// @brief Construct an empty OptionValue object.
    OptionValue();

    /// @brief Construct a new OptionValue object as integer
    /// @param int_val 
    OptionValue(int int_val);

    OptionValue(double double_val);

    OptionValue(const std::string& string_val);

    OptionValue(bool bool_val);
private:
    DataType m_datatype;
    int m_intVal;
    double m_doubleVal;
    bool m_boolVal;
    std::string m_stringVal;
};

struct Option
{
    OptionValue value;
    OptionValue default_value;
};

class OptionManager : public ManagerBase<Option>
{
public:
    /// @brief Parses settings from given file
    /// @param filename Name of the file you want to parse.
    void parseFromFile(const std::string &filename);

    /// @brief Save settings to specified file
    /// @param filename Name of the file you want to save to.
    void saveToFile(const std::string &filename);
private:
};

}

#endif //!_SFEX_MANAGERS_SETTINGSMANAGER_