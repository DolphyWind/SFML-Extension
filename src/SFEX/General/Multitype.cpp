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


Multitype Multitype::null = Multitype();

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
        // Throw an exception because there is no 
        default:
            throw std::runtime_error("Cannot compare values provided!");
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
    if(this->get_datatype() == DataType::LIST) throw std::runtime_error("Cannot add given values!");

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
            return (*this = Multitype::null);
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
        case DataType::STRING:
        case DataType::LIST:
            throw std::runtime_error("Cannot subtract given values!");
            break;
        default:
        case DataType::NONE:
            return (*this = Multitype::null);
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
        case DataType::STRING:
        case DataType::LIST:
            throw std::runtime_error("Cannot multiply given values!");
            break;
        default:
        case DataType::NONE:
            return (*this = Multitype::null);
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
        case DataType::STRING:
        case DataType::LIST:
            throw std::runtime_error("Cannot divide given values!");
            break;
        default:
        case DataType::NONE:
            return (*this = Multitype::null);
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
        case DataType::NONE:
        case DataType::LIST:
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
        case DataType::LIST:
        {
            auto vec = this->as_list();
            std::string output = "[";
            for(std::size_t i = 0; i < vec.size(); i++)
            {
                std::string stringified = vec[i].to_string();
                if(vec[i].get_datatype() == DataType::STRING) stringified = '\"' + stringified + '\"';
                output += stringified;

                if(i != vec.size() - 1) output += ", ";
            }
            output += "]";
            return output;
        }
        default:
        case DataType::NONE:
            break;
    }
    return std::string("null");
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
    return DataType::NONE;
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