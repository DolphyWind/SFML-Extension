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

#include <SFEX/Managers/OptionManager.hpp>

namespace sfex
{

OptionValue OptionValue::empty = OptionValue();

OptionValue::OptionValue(OptionValue::DataType datatype): m_datatype(DataType::NONE), m_data(nullptr), m_size(0)
{
    if(datatype == DataType::NONE) return;
    reset(datatype);
}

OptionValue::OptionValue(const OptionValue& other)
{
    update_value(other.m_size, other.m_data.get(), other.m_datatype);
}

OptionValue::OptionValue(OptionValue&& other)
{
    update_value(other.m_size, other.m_data.get(), other.m_datatype);
    other.cleanup();
}

OptionValue::OptionValue(int int_val): m_datatype(DataType::INT), m_data(nullptr), m_size(sizeof(int))
{
    update_value(m_size, &int_val, m_datatype);
}

OptionValue::OptionValue(double double_val): m_datatype(DataType::DOUBLE), m_data(nullptr), m_size(sizeof(double))
{
    update_value(m_size, &double_val, m_datatype);
}

OptionValue::OptionValue(bool bool_val): m_datatype(DataType::BOOLEAN), m_data(nullptr), m_size(sizeof(bool))
{
    update_value(m_size, &bool_val, m_datatype);
}

OptionValue::OptionValue(const char* charptr_val): m_datatype(DataType::STRING), m_data(nullptr), m_size(0)
{
    update_value(strlen(charptr_val)+1, (void*)charptr_val, DataType::STRING);
    *(m_data.get() + m_size - 1) = '\0';
}

OptionValue::OptionValue(const std::string &string_val): m_datatype(DataType::STRING), m_data(nullptr), m_size(string_val.size())
{
    update_value(m_size, (void*)string_val.c_str(), m_datatype);
}

OptionValue::~OptionValue()
{
    cleanup();
}

bool OptionValue::operator==(const OptionValue &other) const
{
    if(this->get_datatype() != other.get_datatype()) return false;
    switch (this->get_datatype())
    {
        case DataType::BOOLEAN:
            return this->as_bool() == other.as_bool();
        case DataType::DOUBLE:
            return this->as_double() == other.as_double();
        case DataType::INT:
            return this->as_int() == other.as_int();
        case DataType::STRING:
            return this->as_string() == other.as_string();
        // Return true when datatype is none becase (nullptr == nullptr) evaluate to true
        default:
            return true;
    }
}

bool OptionValue::operator!=(const OptionValue &other) const
{
    return !((*this) == other);
}

bool OptionValue::operator<(const OptionValue &other) const
{
    if(this->get_datatype() != other.get_datatype()) throw std::runtime_error("Cannot compare two things with different datatypes!");

    switch (this->get_datatype())
    {
        case DataType::BOOLEAN:
            return this->as_bool() < other.as_bool();
        case DataType::DOUBLE:
            return this->as_double() < other.as_double();
        case DataType::INT:
            return this->as_int() < other.as_int();
        case DataType::STRING:
            return this->as_string() < other.as_string();
        // Throw an exception because there is no 
        default:
            throw std::runtime_error("Cannot compare two None values!");
    }
}

bool OptionValue::operator<=(const OptionValue &other) const
{
    return (*this < other) || (*this == other);
}

bool OptionValue::operator>(const OptionValue &other) const
{
    return !(*this <= other);
}

bool OptionValue::operator>=(const OptionValue &other) const
{
    return !(*this < other);
}

OptionValue& OptionValue::operator+=(const OptionValue &other)
{
    if(this->get_datatype() != other.get_datatype()) throw std::runtime_error("Cannot add two values with different types!");

    switch (this->get_datatype())
    {
        case DataType::BOOLEAN:
            return (*this = (this->as_bool() + other.as_bool()));
        case DataType::DOUBLE:
            return (*this = (this->as_double() + other.as_double()));
        case DataType::INT:
            return (*this = (this->as_int() + other.as_int()));
        case DataType::STRING:
            return (*this = (this->as_string() + other.as_string()));
        default:
        case DataType::NONE:
            return (*this = OptionValue::empty);
    }
}

OptionValue OptionValue::operator+(const OptionValue &other) const
{
    return (OptionValue(*this) += other);
}

OptionValue& OptionValue::operator-=(const OptionValue &other)
{
    if(this->get_datatype() != other.get_datatype()) throw std::runtime_error("Cannot subtract two values with different types!");

    switch (this->get_datatype())
    {
        case DataType::BOOLEAN:
            return (*this = (this->as_bool() - other.as_bool()));
        case DataType::DOUBLE:
            return (*this = (this->as_double() - other.as_double()));
        case DataType::INT:
            return (*this = (this->as_int() - other.as_int()));
        case DataType::STRING:
            throw std::runtime_error("Cannot subtract strings.");
            break;
        default:
        case DataType::NONE:
            return (*this = OptionValue::empty);
    }
}

OptionValue OptionValue::operator-(const OptionValue &other) const
{
    return (OptionValue(*this) -= other);
}

OptionValue& OptionValue::operator*=(const OptionValue &other)
{
    if(this->get_datatype() != other.get_datatype()) throw std::runtime_error("Cannot multiply two values with different types!");

    switch (this->get_datatype())
    {
        case DataType::BOOLEAN:
            return (*this = (this->as_bool() * other.as_bool()));
        case DataType::DOUBLE:
            return (*this = (this->as_double() * other.as_double()));
        case DataType::INT:
            return (*this = (this->as_int() * other.as_int()));
        case DataType::STRING:
            throw std::runtime_error("Cannot multiply strings.");
            break;
        default:
        case DataType::NONE:
            return (*this = OptionValue::empty);
    }
}

OptionValue OptionValue::operator*(const OptionValue &other) const
{
    return (OptionValue(*this) *= other);
}

OptionValue& OptionValue::operator/=(const OptionValue &other)
{
    if(this->get_datatype() != other.get_datatype()) throw std::runtime_error("Cannot divide two values with different types!");

    switch (this->get_datatype())
    {
        case DataType::BOOLEAN:
            return (*this = (this->as_bool() / other.as_bool()));
        case DataType::DOUBLE:
            return (*this = (this->as_double() / other.as_double()));
        case DataType::INT:
            return (*this = (this->as_int() / other.as_int()));
        case DataType::STRING:
            throw std::runtime_error("Cannot divide strings.");
            break;
        default:
        case DataType::NONE:
            return (*this = OptionValue::empty);
    }
}

OptionValue OptionValue::operator/(const OptionValue &other) const
{
    return (OptionValue(*this) /= other);
}

OptionValue& OptionValue::operator=(const OptionValue &other)
{
    update_value(other.m_size, other.m_data.get(), other.m_datatype);
    return *this;
}

template<typename T>
OptionValue& OptionValue::operator=(const T &other)
{
    return (*this = OptionValue(other));
}

OptionValue& OptionValue::reset(DataType datatype)
{
    switch (datatype)
    {
        case DataType::BOOLEAN:
        {
            bool default_value = false;
            update_value(sizeof(bool), &default_value, datatype);
            break;
        }
        case DataType::DOUBLE:
        {
            double default_value = 0.0;
            update_value(sizeof(double), &default_value, datatype);
            break;
        }
        case DataType::INT:
        {
            int default_value = 0;
            update_value(sizeof(int), &default_value, datatype);
            break;
        }
        case DataType::STRING:
        {
            std::string default_value;
            update_value(default_value.length() + 1, (void*)default_value.c_str(), datatype);
            break;
        }
        default:
        case DataType::NONE:
        {
            m_datatype = DataType::NONE;
            m_data = nullptr;
            m_size = 0;
            break;
        }
    }
    return *this;
}

std::string OptionValue::to_string() const
{
    switch (m_datatype)
    {
        case DataType::BOOLEAN:
        {
            if(this->as_bool()) return "true";
            return "false";
        }
        case DataType::DOUBLE:
        {
            std::string double_as_str = std::to_string(this->as_double());
            if(double_as_str.find('.') != std::string::npos)
            {
                while(double_as_str[double_as_str.length() - 1] == '0' && double_as_str[double_as_str.length() - 2] != '.') double_as_str.erase(double_as_str.length() - 1);
            }
            return double_as_str;
        }
        case DataType::INT:
        {
            return std::to_string(this->as_int());
        }
        case DataType::STRING:
        {
            return this->as_string();
        }
        default:
        case DataType::NONE:
            break;
    }
    return std::string("null");
}

OptionValue::DataType OptionValue::get_datatype() const
{
    return m_datatype;
}

std::string OptionValue::get_datatype_as_string() const
{
    switch (m_datatype)
    {
        case DataType::BOOLEAN:
            return "bool";
        case DataType::DOUBLE:
            return "double";
        case DataType::INT:
            return "int";
        case DataType::STRING:
            return "string";
        case DataType::NONE:
        default:
            return "none";
    }
}

OptionValue::DataType OptionValue::string_to_datatype(const std::string &str)
{
    std::string copy_str = str;
    for(auto &c : copy_str)
    {
        c = std::tolower(c);
    }
    if(copy_str == "bool" || copy_str == "boolean") return DataType::BOOLEAN;
    if(copy_str == "double") return DataType::DOUBLE;
    if(copy_str == "int" || copy_str == "integer") return DataType::INT;
    if(copy_str == "string") return DataType::STRING;
    return DataType::NONE;
}

int OptionValue::as_int() const
{
    if(m_datatype != DataType::INT) return 0;
    return *reinterpret_cast<int*>(m_data.get());
}

OptionValue::operator int() const
{
    return this->as_int();
}

double OptionValue::as_double() const
{
    if(m_datatype != DataType::DOUBLE) return 0.0;
    return *reinterpret_cast<double*>(m_data.get());
}

OptionValue::operator double() const
{
    return this->as_double();
}

bool OptionValue::as_bool() const
{
    if(m_datatype != DataType::BOOLEAN) return false;
    return *reinterpret_cast<bool*>(m_data.get());
}

OptionValue::operator bool() const
{
    return this->as_bool();
}

std::string OptionValue::as_string() const
{
    if(m_datatype != DataType::STRING) return std::string();
    return std::string(m_data.get());
}

OptionValue::operator std::string() const
{
    return this->as_string();
}

std::ostream& operator<<(std::ostream &left, const OptionValue &right)
{
    left << right.to_string();
    return left;
}

void OptionValue::cleanup()
{
    m_data = nullptr;
    m_size = 0;
    m_datatype = DataType::NONE;
}

void OptionValue::update_value(std::size_t new_size, void* new_data, const DataType &datatype)
{
    m_size = new_size;
    m_datatype = datatype;
    m_data.reset(new char[new_size]);
    std::memcpy(m_data.get(), new_data, m_size);
}

void Option::reset()
{
    this->value = this->default_value;
}

void OptionManager::updateOption(const std::string &key, const OptionValue &val)
{
    if(this->contains(key)) this->at(key).value = val;
    else addOption(key, val, OptionValue(val.get_datatype()));
}

void OptionManager::addOption(const std::string &key, const OptionValue &val, const OptionValue &default_val)
{
    if(this->contains(key)) return;

    this->insert({key, {val, default_val}});
}

bool OptionManager::parseFromFile(const std::string &filename, bool create_file_if_not_exists)
{
    std::ifstream file(filename);
    if(file)
    {
        // Read all lines into a vector called parsed_strings
        std::vector<std::string> lines;
        std::string tmp_line;
        while(std::getline(file, tmp_line)) lines.push_back(tmp_line);

        std::vector<std::vector<std::string>> parsed_strings;
        bool in_quotes = false;
        for(auto& line : lines)
        {
            unsigned short parsed_count = 0;
            std::string current_parsed;
            std::vector<std::string> line_parsed;

            for(std::size_t i = 0; i < line.length(); i++)
            {
                if(parsed_count == 3) break;
                if(line[i] == '\"')
                {
                    in_quotes = !in_quotes;
                    continue;
                }

                if(line[i] == ' ' && !in_quotes)
                {
                    if(current_parsed.empty()) continue;
                    parsed_count += 1;
                    line_parsed.push_back(current_parsed);
                    current_parsed.clear();
                }
                else
                {
                    current_parsed.push_back(line[i]);
                }
            }
            if(!current_parsed.empty()) line_parsed.push_back(current_parsed);
            if(line_parsed.size() < 3) return false; // Error there needs to be at least 3 strings that is parsed
            parsed_strings.push_back(line_parsed);
        }

        for(auto &pline : parsed_strings)
        {
            OptionValue::DataType datatype = OptionValue::string_to_datatype(pline[0]);
            std::string key_to_insert = pline[1];

            OptionValue current_value;

            switch (datatype)
            {
                case OptionValue::DataType::BOOLEAN:
                {
                    for(auto &c : pline[2])
                    {
                        c = std::tolower(c);
                    }
                    std::vector<std::string> false_strings = {
                        "0", "false", "f", "n", "no"
                    };
                    if(std::find(false_strings.begin(), false_strings.end(), pline[2]) != false_strings.end()) current_value = false;
                    else current_value = true;
                    break;
                }
                case OptionValue::DataType::DOUBLE:
                {
                    current_value = std::stod(pline[2]);
                    break;
                }
                case OptionValue::DataType::INT:
                {
                    current_value = std::stoi(pline[2]);
                    break;
                }
                case OptionValue::DataType::STRING:
                {
                    current_value = pline[2];
                    break;
                }
                default:
                case OptionValue::DataType::NONE:
                {
                    break;
                }
            }

            // this->insert({key_to_insert, current_value});
            updateOption(key_to_insert, current_value);
        }
        
        return true;
    }
    if(create_file_if_not_exists)
    {
        // If can't load file and create_file_if_not_exists is true try to create file
        return saveToFile(filename);
    }
    return false;
}

bool OptionManager::saveToFile(const std::string &filename)
{
    std::ofstream file(filename);
    if(!file) return false;

    for(auto&[key, option] : this->m_hashmap)
    {
        file << option.value.get_datatype_as_string() << " " << key << " \"" << option.value.to_string() << "\"\n";
    }
    file.close();
    return true;
}

}
