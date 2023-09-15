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

#include <SFEX/General/Multitype.hpp>

namespace sfex
{

const Multitype Multitype::null = Multitype();

Multitype::Multitype(Multitype::DataType datatype): m_datatype(DataType::NONE), m_data(nullptr), m_size(0)
{
    if(datatype == DataType::NONE) return;
    reset(datatype);
}

Multitype::Multitype(const Multitype& other)
{
    update_value(other.m_size, other.m_data.get(), other.m_datatype);
}

Multitype::Multitype(Multitype&& other)
{
    update_value(other.m_size, other.m_data.get(), other.m_datatype);
    other.cleanup();
}

Multitype::Multitype(int int_val): m_datatype(DataType::INT), m_data(nullptr), m_size(sizeof(int))
{
    update_value(m_size, &int_val, m_datatype);
}

Multitype::Multitype(double double_val): m_datatype(DataType::DOUBLE), m_data(nullptr), m_size(sizeof(double))
{
    update_value(m_size, &double_val, m_datatype);
}

Multitype::Multitype(const char* charptr_val): m_datatype(DataType::STRING), m_data(nullptr), m_size(std::strlen(charptr_val)+1)
{
    update_value(m_size, (void*)charptr_val, DataType::STRING);
}

Multitype::Multitype(const std::string &string_val): m_datatype(DataType::STRING), m_data(nullptr), m_size(string_val.size() + 1)
{
    update_value(m_size, (void*)string_val.c_str(), m_datatype);
}

Multitype::Multitype(bool bool_val): m_datatype(DataType::BOOLEAN), m_data(nullptr), m_size(sizeof(bool))
{
    update_value(m_size, &bool_val, m_datatype);
}

Multitype::Multitype(const std::vector<Multitype> &vec_val): m_datatype(DataType::LIST), m_data(nullptr), m_size(vec_val.size() * sizeof(Multitype))
{
    // Convert option value vector into an array
    std::unique_ptr<Multitype[]> values = std::make_unique<Multitype[]>(vec_val.size());
    for(std::size_t i = 0; i < vec_val.size(); i++)
    {
        *(values.get() + i) = vec_val[i];
    }
    update_value(m_size, values.release(), m_datatype);
}

Multitype::Multitype(const std::vector<int>& int_vector): m_datatype(DataType::LIST), m_data(nullptr), m_size(int_vector.size() * sizeof(Multitype))
{
    std::unique_ptr<Multitype[]> values = std::make_unique<Multitype[]>(int_vector.size());
    for(std::size_t i = 0 ; i < int_vector.size(); ++i)
    {
        *(values.get() + i) = int_vector[i];
    }
    update_value(m_size, values.release(), m_datatype);
}


Multitype::Multitype(const std::vector<double>& double_vector): m_datatype(DataType::LIST), m_data(nullptr), m_size(double_vector.size() * sizeof(Multitype))
{
    std::unique_ptr<Multitype[]> values = std::make_unique<Multitype[]>(double_vector.size());
    for(std::size_t i = 0 ; i < double_vector.size(); ++i)
    {
        *(values.get() + i) = double_vector[i];
    }
    update_value(m_size, values.release(), m_datatype);
}

Multitype::Multitype(const std::vector<bool>& bool_vector): m_datatype(DataType::LIST), m_data(nullptr), m_size(bool_vector.size() * sizeof(Multitype))
{
    std::unique_ptr<Multitype[]> values = std::make_unique<Multitype[]>(bool_vector.size());
    for(std::size_t i = 0 ; i < bool_vector.size(); ++i)
    {
        *(values.get() + i) = bool_vector[i];
    }
    update_value(m_size, values.release(), m_datatype);
}

Multitype::Multitype(const std::vector<std::string>& string_vector): m_datatype(DataType::LIST), m_data(nullptr), m_size(string_vector.size() * sizeof(Multitype))
{
    std::unique_ptr<Multitype[]> values = std::make_unique<Multitype[]>(string_vector.size());
    for(std::size_t i = 0 ; i < string_vector.size(); ++i)
    {
        *(values.get() + i) = string_vector[i];
    }
    update_value(m_size, values.release(), m_datatype);
}

Multitype::Multitype(const std::initializer_list<Multitype> &list_val)
{
    *this = Multitype(std::vector<Multitype>(list_val.begin(), list_val.end()));
}

Multitype::Multitype(const MultitypeMap &map_val): m_datatype(DataType::MAP), m_data(nullptr), m_size((sizeof(Multitype)+sizeof(char*))*map_val.size())
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

Multitype::Multitype(const std::initializer_list<std::pair<std::string, Multitype>> &pair_initializer_list)
{
    *this = Multitype(MultitypeMap(pair_initializer_list.begin(), pair_initializer_list.end()));
}

Multitype::~Multitype()
{
    cleanup();
}

bool Multitype::operator==(const Multitype &other) const
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
        case DataType::LIST:
            return this->as_list() == other.as_list();
        case DataType::MAP:
            return this->as_map() == other.as_map();
        // Return true when datatype is none becase (nullptr == nullptr) evaluate to true
        default:
            return true;
    }
}

bool Multitype::operator!=(const Multitype &other) const
{
    return !((*this) == other);
}

bool Multitype::operator<(const Multitype &other) const
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
        default:
            throw std::runtime_error("Cannot compare given values!");
    }
}

bool Multitype::operator<=(const Multitype &other) const
{
    return (*this < other) || (*this == other);
}

bool Multitype::operator>(const Multitype &other) const
{
    return !(*this <= other);
}

bool Multitype::operator>=(const Multitype &other) const
{
    return !(*this < other);
}

Multitype& Multitype::operator+=(const Multitype &other)
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
        case DataType::NONE:
            return (*this = Multitype::null);
        default:
            throw std::runtime_error("Cannot add given values!");
            break;
    }
}

Multitype Multitype::operator+(const Multitype &other) const
{
    return (Multitype(*this) += other);
}

Multitype& Multitype::operator-=(const Multitype &other)
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
        case DataType::NONE:
            return (*this = Multitype::null);
        default:
            throw std::runtime_error("Cannot subtract given values!");
            break;
    }
}

Multitype Multitype::operator-(const Multitype &other) const
{
    return (Multitype(*this) -= other);
}

Multitype& Multitype::operator*=(const Multitype &other)
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
        case DataType::NONE:
            return (*this = Multitype::null);
        default:
            throw std::runtime_error("Cannot multiply given values!");
            break;
    }
}

Multitype Multitype::operator*(const Multitype &other) const
{
    return (Multitype(*this) *= other);
}

Multitype& Multitype::operator/=(const Multitype &other)
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
        case DataType::NONE:
            return (*this = Multitype::null);
        default:
            throw std::runtime_error("Cannot divide given values!");
            break;
    }
}

Multitype Multitype::operator/(const Multitype &other) const
{
    return (Multitype(*this) /= other);
}

Multitype& Multitype::operator=(const Multitype &other)
{
    update_value(other.m_size, other.m_data.get(), other.m_datatype);
    return *this;
}

const Multitype Multitype::operator[](std::size_t index)
{
    return this->as_list()[index];
}

const Multitype Multitype::operator[](const std::string& key)
{
    return this->as_map()[key];
}

const Multitype Multitype::operator[](const char* key)
{
    return this->as_map()[key];
}

Multitype& Multitype::reset(DataType datatype)
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
        {
            update_value(0, nullptr, datatype);
            break;
        }
    }
    return *this;
}

std::string Multitype::to_string() const
{
    return to_string_priv(false, false, 0, false);
}

std::string Multitype::serialize(bool prettify) const
{
    return to_string_priv(true, prettify, 0, false);
}

std::string Multitype::to_string_priv(bool serialize, bool prettify, std::size_t indent, bool special_prettify) const
{
    std::string indent_str;
    if(prettify) 
    {
        indent_str = std::string(indent, ' ');
        if(special_prettify)
        {
            if(get_datatype() != DataType::LIST && get_datatype() != DataType::MAP) indent_str = "";
        }
    }

    switch (m_datatype)
    {
        case DataType::BOOLEAN:
        {
            if(this->as_bool()) return indent_str + "true";
            return indent_str + "false";
        }
        case DataType::DOUBLE:
        {
            std::string double_as_str = std::to_string(this->as_double());
            if(double_as_str.find('.') != std::string::npos)
            {
                while(double_as_str[double_as_str.length() - 1] == '0' && double_as_str[double_as_str.length() - 2] != '.') double_as_str.erase(double_as_str.length() - 1);
            }
            return indent_str + double_as_str;
        }
        case DataType::INT:
        {
            return indent_str + std::to_string(this->as_int());
        }
        case DataType::STRING:
        {
            if(serialize) return indent_str + "\"" + this->as_string() + "\"";
            return indent_str + this->as_string();
        }
        case DataType::LIST:
        {
            auto vec = this->as_list();
            if(vec.empty())
            {
                if(!special_prettify) return indent_str + "[]";
                return "[]";
            }
            std::stringstream out;
            if(!special_prettify) out << indent_str;
            out << "[";
            if(prettify) out << '\n';
            for(std::size_t i = 0; i < vec.size(); i++)
            {
                std::string stringified = vec[i].to_string_priv(serialize, prettify, indent + 4, false);
                out << stringified;

                if(i != vec.size() - 1) out << ", ";
                if(prettify) out << '\n';
            }
            out << indent_str << "]";
            return out.str();
        }
        case DataType::MAP:
        {
            MultitypeMap map = this->as_map();
            if(map.empty())
            {
                if(!special_prettify) return indent_str + "{}";
                return "{}";
            }
            std::stringstream out;
            if(!special_prettify) out << indent_str;
            out << "{";
            if(prettify) out << '\n';
            std::size_t i = 0;
            for(auto &[key, value] : map)
            {
                if(prettify) out << indent_str << std::string(4, ' ');
                out << '\"' << key << "\": " << value.to_string_priv(serialize, prettify, indent + 4, true);
                if(i != map.size() - 1) out << ", ";
                if(prettify) out << '\n';
                i++;
            }
            out << indent_str << "}";
            return out.str();
        }
        default:
            return indent_str + std::string("null");
            break;
    }
}

Multitype::DataType Multitype::get_datatype() const
{
    return m_datatype;
}

std::string Multitype::get_datatype_as_string() const
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
        case DataType::LIST:
            return "list";
        case DataType::MAP:
            return "map";
        case DataType::NONE:
        default:
            return "none";
    }
}

Multitype::DataType Multitype::string_to_datatype(const std::string &str)
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
    if(copy_str == "list") return DataType::LIST;
    if(copy_str == "map") return DataType::MAP;
    return DataType::NONE;
}

Multitype Multitype::parse(const std::string &str)
{
    auto strip = [](const std::string& str)->std::string
    {
        auto start = std::find_if(str.begin(), str.end(), [](char ch){
            return !std::isspace(ch) && ch != '\t' && ch != '\n';
        });
        auto end = std::find_if(str.rbegin(), str.rend(), [](char ch){
            return !std::isspace(ch) && ch != '\t' && ch != '\n';
        }).base();
        if(end < start) return std::string();
        return std::string(start, end);
    };

    // First, strip string.
    std::string str_to_parse = strip(str);

    auto parse_integer = [](const std::string& str)->std::optional<int>{
        try
        {
            std::size_t pos = 0;
            int result = std::stoi(str, &pos);
            if (pos != str.length()) return std::nullopt;
            return result;
        }
        catch (const std::exception&)
        {
            return std::nullopt;
        }
    };

    auto parse_double = [](const std::string& str)->std::optional<double>{
        try
        {
            std::size_t pos = 0;
            double result = std::stod(str, &pos);
            if (pos != str.length()) return std::nullopt;
            return result;
        }
        catch (const std::exception&)
        {
            return std::nullopt;
        }
    };

    auto split_from_commas = [](const std::string& str)->std::vector<std::string>
    {
        bool inside_string = false;
        long list_depth = 0;
        long map_depth = 0;

        std::vector<std::size_t> comma_positions;
        for(std::size_t i = 0; i < str.length(); i++)
        {
            char c = str[i];

            if(c == '\"') inside_string = !inside_string;
            else if(c == '[' && !inside_string) list_depth++;
            else if(c == '{' && !inside_string) map_depth++;
            else if(c == ']' && !inside_string) list_depth--;
            else if(c == '}' && !inside_string) map_depth--;

            if(list_depth < 0 || map_depth < 0) throw std::runtime_error("Parse Error: Invalid brackets while parsing JSON");

            if(!inside_string && list_depth == 0 && map_depth == 0 && c == ',') comma_positions.push_back(i);
        }
        comma_positions.push_back(str.length());

        std::vector<std::string> output;
        output.push_back(str.substr(0, comma_positions[0]));
        for(std::size_t i = 0; i < comma_positions.size() - 1; i++)
        {
            output.push_back(str.substr(comma_positions[i] + 1, comma_positions[i + 1] - comma_positions[i] - 1));
        }

        return output;
    };

    auto parse_string = [&](const std::string& str)->std::string
    {
        std::string stripped = strip(str);
        std::string str_without_quotes = std::string(stripped.begin() + 1, stripped.end() - 1);
        return str_without_quotes;
    };

    auto parse_pair = [&](const std::string& str, bool throw_when_empty=true)->std::pair<std::string, Multitype>
    {
        std::string stripped = strip(str);
        if(stripped.empty() && throw_when_empty) throw std::invalid_argument("Parse Error: Empty string cannot be parsed as a pair.");
        std::size_t column_pos = stripped.find(':');
        if(column_pos == std::string::npos) throw std::runtime_error("Parse Error: Cannot parse pair. No column found.");
        std::string key_str = stripped.substr(0, column_pos);
        std::string value_str = stripped.substr(column_pos + 1, stripped.length() - column_pos - 1);

        std::string key = parse_string(key_str);
        Multitype value = Multitype::parse(value_str);
        return {key, value};
    };

    if(str_to_parse[0] == '{')
    {
        if(str_to_parse[str_to_parse.length() - 1] != '}') throw std::runtime_error("Parse Error: Cannot parse \"" + str_to_parse + "\" into a map.");
        MultitypeMap result;
        auto comma_splitted = split_from_commas(str_to_parse.substr(1, str_to_parse.length() - 2));
        for(auto &s : comma_splitted)
        {
            try
            {
                auto pair = parse_pair(s, (comma_splitted.size() == 1));
                result.insert(pair);
            }
            catch(std::invalid_argument&)
            {
                // Do nothing 
            }
        }
        return result;
    }
    if(str_to_parse[0] == '[')
    {
        if(str_to_parse[str_to_parse.length() - 1] != ']') throw std::runtime_error("Parse Error: Cannot parse \"" + str_to_parse + "\" into a list.");
        std::vector<Multitype> result;
        for(auto &s : split_from_commas(str_to_parse.substr(1, str_to_parse.length() - 2)))
        {
            try
            {
                Multitype elem = Multitype::parse(s);
                result.push_back(elem);
            }
            catch(const std::invalid_argument&)
            {
                // Do nothing
            }
        }
        return result;
    }
    if(str_to_parse[0] == '\"')
    {
        if(str_to_parse[str_to_parse.length() - 1] != '\"') throw std::runtime_error("Parse Error: Cannot parse '" + str_to_parse + "' into a string.");
        return parse_string(str_to_parse);
    }
    if(str_to_parse == "true") return true;
    if(str_to_parse == "false") return false;
    if(str_to_parse == "null") return Multitype::null;
    
    std::optional<int> try_parse_int = parse_integer(str_to_parse);
    if(try_parse_int != std::nullopt) return try_parse_int.value();
    
    std::optional<double> try_parse_double = parse_double(str_to_parse);
    if(try_parse_double != std::nullopt) return try_parse_double.value();

    if(str_to_parse.empty()) throw std::invalid_argument("Cannot parse empty string!");
    return Multitype::null;
}

int Multitype::as_int() const
{
    if(m_datatype != DataType::INT) return 0;
    return *reinterpret_cast<int*>(m_data.get());
}

Multitype::operator int() const
{
    return this->as_int();
}

double Multitype::as_double() const
{
    if(m_datatype != DataType::DOUBLE) return 0.0;
    return *reinterpret_cast<double*>(m_data.get());
}

Multitype::operator double() const
{
    return this->as_double();
}

bool Multitype::as_bool() const
{
    if(m_datatype != DataType::BOOLEAN) return false;
    return *reinterpret_cast<bool*>(m_data.get());
}

Multitype::operator bool() const
{
    return this->as_bool();
}

std::string Multitype::as_string() const
{
    if(m_datatype != DataType::STRING) return std::string();
    return std::string(m_data.get());
}

Multitype::operator std::string() const
{
    return this->as_string();
}

std::vector<Multitype> Multitype::as_list() const
{
    if(m_datatype != DataType::LIST) return std::vector<Multitype>();

    return std::vector<Multitype>(reinterpret_cast<Multitype*>(m_data.get()), reinterpret_cast<Multitype*>(m_data.get()) + m_size / sizeof(Multitype));
}

Multitype::operator std::vector<Multitype>() const
{
    return this->as_list();
}

MultitypeMap Multitype::as_map() const
{
    if(m_datatype != DataType::MAP) MultitypeMap();

    struct Pair
    {
        std::unique_ptr<const char[]> char_ptr;
        Multitype multitype;
    };
    
    Pair* p = reinterpret_cast<Pair*>(m_data.get());
    MultitypeMap result;

    for(std::size_t i = 0; i < m_size / sizeof(Pair); i++)
    {
        result[std::string(p->char_ptr.get())] = p->multitype;
        p++;
    }
    return result;
}

Multitype::operator MultitypeMap() const
{
    return this->as_map();
}

std::ostream& operator<<(std::ostream &left, const Multitype &right)
{
    left << right.to_string();
    return left;
}

void Multitype::cleanup()
{
    m_data = nullptr;
    m_size = 0;
    m_datatype = DataType::NONE;
}

void Multitype::update_value(std::size_t new_size, void* new_data, const DataType &datatype)
{
    m_size = new_size;
    m_datatype = datatype;
    m_data.reset(new char[new_size]);
    std::memcpy(m_data.get(), new_data, m_size);
}

}