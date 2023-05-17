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
#include <SFEX/General/Multitype.hpp>
#include <vector>
#include <cstring>
#include <memory>
#include <ostream>
#include <fstream>
#include <algorithm>

namespace sfex
{

/// @brief Option struct that stores value and the default value of an option
struct Option
{
    Multitype value;
    const Multitype default_value;

    void reset();
};

/// @brief Simple OptionManager that stores Options in a hashmap. It can also read from a file and write to a file. Inherits from ManagerBase<sfex::Option>
class OptionManager : public ManagerBase<Option>
{
public:
    /// @brief Updates an option of OptionManager. Inserts a new option if key is not present.
    /// @param key Key of the new option
    /// @param val New option
    void updateOption(const std::string &key, const Multitype &val);

    /// @brief Adds a new option to OptionManager. Does nothing if key is already present.
    /// @param key Key of the new option
    /// @param val New option value
    /// @param default_val Default value of that option
    void addOption(const std::string &key, const Multitype &val, const Multitype &default_val);

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