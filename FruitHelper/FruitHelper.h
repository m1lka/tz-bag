#pragma once

#include <string>
#include <set>
#include "Fruit.h"

namespace FruitHelper
{
    static std::hash<std::string> HashString;

    struct CompareByHash
    {
        bool operator()(const Fruit& left, const Fruit& right) const
        {
            return (left.GetHashName() < right.GetHashName());
        }
    };

    using FruitVariant_type = std::set<Fruit, FruitHelper::CompareByHash>;
    using FruitVariant_iterator = FruitVariant_type::iterator;
}
