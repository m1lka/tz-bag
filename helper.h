#pragma once

#include <algorithm>
#include <string>
#include <stdexcept>

inline void is_digits(const std::string &s)
{
    if(s.find_first_not_of("-.0123456789") != std::string::npos)
        throw std::logic_error("The parameter \'" + s + "\' must contain only digits");
}

inline void is_letters(const std::string &s)
{
    if(!std::all_of(s.begin(), s.end(), ::isalpha))
        throw std::logic_error("The parameter \'" + s + "\' must contain only letters");
}
