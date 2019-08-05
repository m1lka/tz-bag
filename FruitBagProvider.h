#ifndef _FRUITBAGPROVIDER_H
#define _FRUITBAGPROVIDER_H

#include "Fruit.h"
#include "Services/IService.h"

class FruitBagProvider
{
public:
    FruitBagProvider(IService* service);
    ~FruitBagProvider();
	
    void Add(std::string fruitName, int fruitCount);
    void Remove(std::string fruitName, int fruitCount);
    void Print();
	
private:
    std::set<Fruit, FruitHelper::CompareByHash>* _fruitVariants;
    std::map<Fruit, int, FruitHelper::CompareByHash> _bag;
	
    std::set<Fruit, FruitHelper::CompareByHash>::iterator findFruitVariant(std::string& fruitName);
    void checkCount(int fruitCount);
};

#endif
