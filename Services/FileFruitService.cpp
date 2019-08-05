#include "Services/FileFruitService.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "helper.h"

using namespace std;

FileFruitService::FileFruitService(string path):
    IService (),
    _path(path)
{

}

void FileFruitService::Load()
{
	cerr << "[INFO] Load fruits from file: " << _path << " start!" << endl << endl;
    ifstream file;

    file.open(_path, ios::in);
    if(!file.is_open())
    {
        throw string("File " + _path + " is not open");
    }

    string fruitLine;
    int numberLine = 0;
    while(getline(file, fruitLine))
    {
		numberLine++;
        if(fruitLine.empty())
        {
            cerr << "Empty line number " << numberLine << " will not be processed\n";
            continue;
        }
        stringstream fruitProp_s(fruitLine);
        string name, weight, price;

        fruitProp_s >> name; fruitProp_s >> weight; fruitProp_s >> price;

        if(!checkParam(name, weight, price))
        {
            cerr << "\tThe line number " << numberLine << " will not be processed." << endl;
            continue;
        }

		string temp;
		fruitProp_s >> temp;

        if(!fruitProp_s.eof() || !temp.empty())
        {
            cerr << "Unknown parameter \'" << temp << "\'" << endl;
			cerr << "\tThe line number " << numberLine << " will not be processed." << endl;
            continue;
        }

        int _weight = atoi(weight.c_str());
        int _price = atoi(price.c_str());

        try
        {
            Fruit fruit(name, _weight, _price);
            auto result = _fruitVariant.insert(fruit);
            if(result.second == false)
            {
                throw string("The fruit has not been added to the list of possible fruit variants");
            }
        }
        catch(string &ex)
        {
            cerr << "Error in line " << numberLine << " with " << name << ":" << endl;
            cerr << "\t" << ex << ". \n\tThe string will not be processed." << endl; cerr .flush();
        }
    }
    cerr << "\n";
    file.close();
	cerr << "[INFO] Load fruits from file: " << _path << " OK." << endl;
}

bool FileFruitService::checkParam(string& name, string& weight , string& price)
{
    if(weight.empty())
    {
        cerr << "Fruit weight is missing\n";
        return false;
    }
    if(price.empty())
    {
        cerr << "Fruit price is missing\n";
        return false;
    }
    try
    {
        is_letters(name);
        is_digits(weight);
        is_digits(price);
    }
    catch (string &ex)
    {
        cerr << "Invalid fruit parameter value:\n\t" << ex << endl;
        return false;
    }
    return true;
}
