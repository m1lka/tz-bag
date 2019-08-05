#ifndef _HELPER_H
#define _HELPER_H

#include <algorithm>
#include <string>

inline void is_digits(std::string &s)
{
    if(s.find_first_not_of("-.0123456789") != std::string::npos)
        throw std::string("The parameter \'" + s + "\' must contain only digits");
}

inline void is_letters(std::string &s)
{
    if(!std::all_of(s.begin(), s.end(), ::isalpha))
        throw std::string("The parameter \'" + s + "\' must contain only letters");
}

#endif
