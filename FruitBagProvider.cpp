#include "FruitBagProvider.h"

#include <iostream>
#include <sstream>

using namespace std;
using namespace FruitHelper;

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

void FruitBagProvider::Add(const string& fruitName, int fruitCount)
{
    FruitVariant_iterator iterVar;

    try
    {
        iterVar = checkCountAndGetVariant(fruitName, fruitCount);
    } catch (std::logic_error&)
    {
        return;
    }

    auto iter = find(*iterVar);
    if(iter != this->end())
        iter->second += fruitCount;
    else
        (*this)[*iterVar] = fruitCount;
}

void FruitBagProvider::Remove(const string& fruitName, int fruitCount)
{
    FruitVariant_iterator iterVar;

    try
    {
        iterVar = checkCountAndGetVariant(fruitName, fruitCount);
    } catch (std::logic_error&)
    {
        return;
    }

    auto iter = find(*iterVar);
    if(iter != end())
    {
        int haveFruits = iter->second;
        if(haveFruits < fruitCount)
        {
            cerr << "You are trying to remove too many \"" << fruitName << "\". There are only " << haveFruits << " fruits.\n";
        }
        else if(haveFruits == fruitCount)
            erase(iter);
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

    for(auto cell: (*this))
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
        throw std::logic_error(error.str());
    }
}

FruitHelper::FruitVariant_iterator FruitBagProvider::findFruitVariant(const string& fruitName)
{
    Fruit fruit(fruitName);

    auto iterVar = _fruitVariants->find(fruit);
    if(iterVar == _fruitVariants->end())
    {
        throw std::logic_error("Fruit \'" + fruitName + "\' not found.");
    }
    return iterVar;
}

FruitHelper::FruitVariant_iterator FruitBagProvider::checkCountAndGetVariant(const std::string& fruitName, int fruitCount)
{
    try {
        auto iterVar = findFruitVariant(fruitName);
        checkCount(fruitCount);
        return iterVar;
    } catch (std::logic_error& ex) {
        cerr << typeid (ex).name() << ":\t" << ex.what() << endl;
        throw;
    }
}
