#ifndef _FRUIT_H
#define _FRUIT_H

#include <string>
#include <map>

namespace FruitHelper {
    static std::hash<std::string> HashString;

    struct CompareByHash;
}

class Fruit
{
public:
    Fruit();
    Fruit(std::string name, int weight, int price);
    Fruit(std::string name);
	
    Fruit& SetName(std::string name);
    Fruit& SetWeight(int weight);
    Fruit& SetPrice(int price);
	
	std::string GetName() const { return _name; }
	int GetWeight() { return _weight; }
	int GetPrice() { return _price; }
    size_t GetHashName() const { return _hashName; }
	
private:
	std::string _name;
	int _weight;
	int _price;
	
    size_t _hashName;
};

namespace FruitHelper {

    struct CompareByHash
    {
        bool operator()(const Fruit& left, const Fruit& right)
        {
            return (left.GetHashName() < right.GetHashName());
        }
    };

}

#endif
