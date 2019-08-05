#ifndef _ISERVICE_HPP
#define _ISERVICE_HPP

#include "../Fruit.h"
#include <set>
#include <iostream>

class IService
{
public:
    IService(): _fruitVariant() {}
    virtual ~IService() {}

    virtual std::set<Fruit, FruitHelper::CompareByHash>& GetFruitVariant()
    {
        return this->_fruitVariant;
    }
    virtual void Load() = 0;

protected:
    std::set<Fruit, FruitHelper::CompareByHash> _fruitVariant;
};

#endif
