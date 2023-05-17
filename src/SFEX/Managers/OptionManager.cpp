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

void Option::reset()
{
    this->value = this->default_value;
}

void OptionManager::updateOption(const std::string &key, const Multitype &val)
{
    if(this->contains(key)) this->at(key).value = val;
    else addOption(key, val, Multitype(val.get_datatype()));
}

void OptionManager::addOption(const std::string &key, const Multitype &val, const Multitype &default_val)
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
            Multitype::DataType datatype = Multitype::string_to_datatype(pline[0]);
            std::string key_to_insert = pline[1];

            Multitype current_value;

            switch (datatype)
            {
                case Multitype::DataType::BOOLEAN:
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
                case Multitype::DataType::DOUBLE:
                {
                    current_value = std::stod(pline[2]);
                    break;
                }
                case Multitype::DataType::INT:
                {
                    current_value = std::stoi(pline[2]);
                    break;
                }
                case Multitype::DataType::STRING:
                {
                    current_value = pline[2];
                    break;
                }
                default:
                case Multitype::DataType::NONE:
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
