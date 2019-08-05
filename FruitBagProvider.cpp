#include "FruitBagProvider.h"

#include <iostream>
#include <sstream>

using namespace std;

FruitBagProvider::FruitBagProvider(IService* service):
    _fruitVariants(nullptr)
{
    service->Load();
    _fruitVariants = &service->GetFruitVariant();
}

FruitBagProvider::~FruitBagProvider()
{
    _fruitVariants = nullptr;
}

void FruitBagProvider::Add(string fruitName, int fruitCount)
{
    set<Fruit, FruitHelper::CompareByHash>::iterator iterVar;

    try {
        iterVar = findFruitVariant(fruitName);
        checkCount(fruitCount);
    } catch (string& ex) {
        cerr << ex << endl;
        return;
    }

    auto iter = _bag.find(*iterVar);
    if(iter != _bag.end())
        iter->second += fruitCount;
    else
        _bag[*iterVar] = fruitCount;
}

void FruitBagProvider::Remove(string fruitName, int fruitCount)
{
    set<Fruit, FruitHelper::CompareByHash>::iterator iterVar;

    try
    {
        iterVar = findFruitVariant(fruitName);
        checkCount(fruitCount);
    }
    catch(string& ex)
    {
        cerr << ex << endl;
        return;
    }

    auto iter = _bag.find(*iterVar);
    if(iter != _bag.end())
    {
        int haveFruits = iter->second;
        if(haveFruits < fruitCount)
        {
            cerr << "You are trying to remove too many \"" << fruitName << "\". There are only " << haveFruits << " fruits.\n";
        }
        else if(haveFruits == fruitCount)
            _bag.erase(iter);
        else
            iter->second -= fruitCount;
    }
    else
        cerr << "Fruit \"" << fruitName << "\" not found in the bag\n";
}

void FruitBagProvider::Print()
{
    stringstream ss;
    ss << "\n============The contents of the bag===================\n";
    ss << "Type\t\tCount\tTotal weight\tTotal price\n";

    int totalWeight = 0, totalPrice = 0;

    for(auto cell: _bag)
    {
        Fruit fruit;
        int totalWeightLine = 0, totalPriceLine = 0;

        fruit = cell.first;
        int fruitCount = cell.second;

        totalWeightLine = fruitCount * fruit.GetWeight();
        totalPriceLine = fruitCount * fruit.GetPrice();
        ss << fruit.GetName() << "\t\t" << fruitCount << "\t" << totalWeightLine << "\t\t" << totalPriceLine << "\n";
        totalWeight += totalWeightLine;
        totalPrice += totalPriceLine;
    }
    ss << "======================================================\n";
    ss << "Total weight:\t" << totalWeight << "\n";
    ss << "Total price:\t" << totalPrice << "\n";
    ss << "======================================================\n";

    cerr << ss.str() << endl;
}

void FruitBagProvider::checkCount(int fruitCount)
{
    if(fruitCount <= 0)
    {
        stringstream error;
        error << "Count couldn't be <= 0 (is " << fruitCount << ")";
        throw error.str();
    }
}

set<Fruit, FruitHelper::CompareByHash>::iterator FruitBagProvider::findFruitVariant(string& fruitName)
{
    Fruit fruit(fruitName);

    auto iterVar = _fruitVariants->find(fruit);
    if(iterVar == _fruitVariants->end())
    {
        throw string("Fruit \'" + fruitName + "\' not found.");
    }
    return iterVar;
}
