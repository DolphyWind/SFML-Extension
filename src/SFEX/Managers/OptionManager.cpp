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

Option::Option(const Multitype& default_value): m_defaultValue(default_value), m_value(default_value)
{
}

Option::Option(const Multitype& value, const Multitype& default_value): m_defaultValue(default_value), m_value(value)
{
}

void Option::reset()
{
    m_value = m_defaultValue;
}

void Option::setValue(const Multitype &new_value)
{
    if(m_defaultValue.get_datatype() != new_value.get_datatype()) throw std::invalid_argument("The datatype of the new value cannot differ from the datatype of the default value");
    m_value = new_value;
}

Multitype Option::getValue() const
{
    return m_value;
}

Multitype Option::getDefaultValue() const
{
    return m_defaultValue;
}

void OptionManager::updateOption(const std::string &key, const Multitype &val)
{
    if(this->contains(key)) this->at(key).setValue(val);
    else addOption(key, val, Multitype(val.get_datatype()));
}

void OptionManager::addOption(const std::string &key, const Multitype &val, const Multitype &default_val)
{
    if(this->contains(key)) return;

    this->insert({key, Option(val, default_val)});
}

bool OptionManager::parseFromFile_JSON(const std::string &filename, bool create_file_if_not_exists)
{
    std::ifstream file(filename);
    if(file)
    {
        // Read file content into a string
        std::string content;
        std::stringstream ss;
        ss << file.rdbuf();
        content = ss.str();

        generateFromMultitype(Multitype::parse(content));
        return true;
    }
    if(create_file_if_not_exists)
    {
        // If can't load file and create_file_if_not_exists is true try to create file
        return saveToFile_JSON(filename);
    }
    return false;
}

bool OptionManager::saveToFile_JSON(const std::string &filename)
{
    std::ofstream file(filename);
    if(!file) return false;
    file << this->to_multitype().serialize();
    file.close();
    return true;
}

Multitype OptionManager::to_multitype() const
{
    MultitypeMap map;
    for(auto &[key, value] : this->m_hashmap)
    {
        map.insert({key, value.getValue()});
    }
    return map;
}

void OptionManager::generateFromMultitype(const Multitype &multitype, bool clear_manager)
{
    if(multitype.get_datatype() != Multitype::DataType::MAP) throw std::invalid_argument("Cannot parse non-map Multitype.");
    if(clear_manager) this->clear();
    
    for(auto &[key, value] : multitype.as_map())
    {
        updateOption(key, value);
    }
}

std::string OptionManager::serialize_JSON() const
{
    return to_multitype().serialize();
}

std::ostream& operator<<(std::ostream& left, const OptionManager& right)
{
    return (left << right.serialize_JSON());
}

}
