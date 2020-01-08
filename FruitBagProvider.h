#pragma once

#include "Fruit.h"
#include "Services/IService.h"
#include "FruitHelper/FruitHelper.h"

class FruitBagProvider: protected std::map<Fruit, int, FruitHelper::CompareByHash>
{
public:
    FruitBagProvider(IService* service);
    ~FruitBagProvider();
	
    void Add(const std::string& fruitName, int fruitCount);
    void Remove(const std::string& fruitName, int fruitCount);
    void Print();
	
private:
    FruitHelper::FruitVariant_type* _fruitVariants;
	
    FruitHelper::FruitVariant_iterator findFruitVariant(const std::string& fruitName);
    void checkCount(int fruitCount);

    FruitHelper::FruitVariant_iterator checkCountAndGetVariant(const std::string& fruitName, int fruitCount);
};
