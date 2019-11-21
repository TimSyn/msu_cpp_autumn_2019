#pragma once

#include <iostream>
#include <list>
#include <sstream>
#include <string>

std::list<std::string> my_split(std::string &my_str, char sep)
{
    std::string tmp_str("");
    std::list<std::string> res;

    size_t counter = 0;
    while (counter != my_str.length())
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

    /*for (std::list<std::string>::const_iterator it = res.begin(); it != res.end(); it++)
        std::cout << *it << std::endl;*/
    return res;
}

enum class Error { NoError, Error };

class Serializer
{
    std::ostream *stream;
    char sep;

public:

    Serializer(std::ostream &stream, char separ = ' ')
    {
        this->stream = &stream;
            sep = separ;
    }

    template <typename T>
    Error Save(const T &data) { return data.serialize(*this); }

    void proc_bool(bool arg) const
    {
        if (arg)
            (*stream) << "true" << sep;
        else
            (*stream) << "false" << sep;
    }

    template <typename T>
    Error operator()(T first) const
    {  
        if (std::is_same<T, bool>::value)
        {
            proc_bool(first);
            return Error::NoError;
        }
        else if (std::is_same<T, std::uint64_t>::value)
        {
            (*stream) << first << sep;
            return Error::NoError;
        }
        else
            return Error::Error;
    }

    template <typename T, typename... Args>
    Error operator()(T first, Args... args) const
    {  
        std::string my_str("");
     
        if (std::is_same<T, bool>::value)
        {
            proc_bool(first);
            if ((*this)(args...) == Error::NoError)
                return Error::NoError;
            else
                return Error::Error;
        }
        else if (std::is_same<T, std::uint64_t>::value)
        {
            (*stream) << first << sep;
            if ((*this)(args...) == Error::NoError)
                return Error::NoError;
            else
                return Error::Error;
        }
        else
            return Error::Error;
    }
};

class Deserializer
{
    std::stringstream* stream;
    char sep;
    std::list<std::string> split_list;
    std::string my_str;

public:
    Deserializer(std::stringstream &stream, char separ = ' ')
    {
        this->stream = &stream;
        my_str = stream.str();
        sep = separ;
        split_list = my_split(my_str, sep);
    }
    
    std::list<std::string>::const_iterator GetIterOnSplitList() const
        { return split_list.begin(); }

    template<typename T>
    Error Load(T &data) { return data.deserialize(*this); }

    template<typename T>
    Error operator()(std::list<std::string>::const_iterator iter, T &first)
    {
        if (iter == split_list.end())
            return Error::Error;

        if (std::is_same<T, bool>::value)
        {
            if (*iter == "true")
                first = true;
            else if (*iter == "false")
                first = false;
            else
                return Error::Error;

            return Error::NoError;
        }
        else if (std::is_same<T, std::uint64_t>::value)
        {
            first = std::stoul(*iter);        
            return Error::NoError;
        }
        else
            return Error::Error;
    }  

    template<typename T, typename... Args>
    Error operator()(std::list<std::string>::const_iterator iter,
                        T &first, Args&... args)
    {
        if (iter == split_list.end())
            return Error::Error;

        if (std::is_same<T, bool>::value)
        {
            if (*iter == "true")
                first = true;
            else if (*iter == "false")
                first = false;
            else
                return Error::Error;

            if ((*this)(++iter, args...) == Error::NoError)
                return Error::NoError;
            else
                return Error::Error;
        }
        else if (std::is_same<T, std::uint64_t>::value)
        {
            first = std::stoul(*iter);
            
            if ((*this)(++iter, args...) == Error::NoError)
                return Error::NoError;
            else
                return Error::Error;
        }
        else
            return Error::Error;
    }  
};
