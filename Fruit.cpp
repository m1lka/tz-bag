#include "Fruit.h"

#include <sstream>
#include <functional>

using namespace std;

Fruit::Fruit():
    _name(""), _weight(0), _price(0), _hashName(0)
{ }

Fruit::Fruit(string name, int weight, int price)
{
    SetName(name).SetWeight(weight).SetPrice(price);
}

Fruit::Fruit(string name)
{
    SetName(name);
    _weight = 0;
    _price = 0;
}

Fruit& Fruit::SetName(string name)
{
    _name = name;
    _hashName = FruitHelper::HashString(_name);

    return *this;
}

Fruit& Fruit::SetWeight(int weight)
{
    if(weight <= 0)
    {
        stringstream error;
        error << "Weight couldn't be <= 0 (is " << weight << ")";
        throw error.str();
    }

    _weight = weight;

    return *this;
}

Fruit& Fruit::SetPrice(int price)
{
    if(price < 0)
    {
        stringstream error;
        error << "Price couldn't be < 0 (is " << price << ")";
        throw error.str();
    }

    _price = price;

    return *this;
}
