#pragma once

#include "../FruitHelper/FruitHelper.h"
#include <set>
#include <iostream>

class IService
{
public:
    IService(): _fruitVariant() {}
    virtual ~IService() {}

    virtual FruitHelper::FruitVariant_type& GetFruitVariant()
    {
        return this->_fruitVariant;
    }
    virtual void Load() = 0;

protected:
    FruitHelper::FruitVariant_type _fruitVariant;
};
