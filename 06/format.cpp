#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

enum class Error { NoError, Error };

void write_to_stream(std::stringstream &stream, char sep)
{}

template <typename T>
void write_to_stream(std::stringstream &stream, char sep,
                        T&& arg)
{
    stream << arg << sep;
}

template <typename T, typename... Args>
void write_to_stream(std::stringstream &stream, char sep,
                        T&& arg, Args&&... args)
{
    stream << arg << sep;
    write_to_stream(stream, sep, args...);
}

std::vector<std::string> my_split(std::string my_str, char sep)
{
    std::string tmp_str("");
    std::vector<std::string> res;

    size_t counter = 0;
    while (counter != my_str.size())
    {
        if (my_str[counter] == sep)
        {
            if (!tmp_str.empty())
                res.push_back(tmp_str);
            tmp_str = std::string("");
            counter++;
            continue;
        }
        tmp_str.append(&my_str[counter], &my_str[counter] + 1);
        counter++;
    }

    return res;
}

template <typename... Args>
std::string format(const std::string &raw_str,
                     Args&&... args)
{
    std::stringstream stream;

    if (raw_str == "")
        return "";

    write_to_stream(stream, ' ', args...);
    std::vector<std::string> word_vect = my_split(stream.str(), ' ');

    std::string new_str("");
    std::string arg_numb("");
    size_t counter = 0;
    bool was_opened = false;
    
    while (raw_str[counter])
    {
        if ((raw_str[counter] == '{') && (!was_opened))
        {
            was_opened = true;
            arg_numb = "";
            counter++;
            continue;
        }
        else if ((raw_str[counter] == '}') && (was_opened))
        {
            int numb = std::stoi(arg_numb), vec_size = word_vect.size();
            
            if ((numb >= 0) && (vec_size > numb))
            {
                new_str.append(word_vect[numb]);
                counter++;
                was_opened = false;
                continue;
            }
            else
                throw std::runtime_error("error");
        }
        else if (((raw_str[counter] == '{') && (was_opened)) ||
                    ((raw_str[counter] == '}') && (!was_opened)))
            throw std::runtime_error("error");

        if (!was_opened)
            new_str.append(&raw_str[counter], &raw_str[counter] + 1);
        else
            arg_numb.append(&raw_str[counter], &raw_str[counter] + 1);
        counter++;    
    }

    return new_str;
}
