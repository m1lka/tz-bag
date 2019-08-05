#include "Console.h"

#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

Console::Console():
    _service(new FileFruitService("./fruits.txt")),
    _bag(_service.get()),
    _running(true)
{
}

void Console::readComand()
{
    string line;
    cerr << "\n:> ";
    getline(cin, line, '\n');

    stringstream ss(line);
    vector<string> values;
    string temp;

    while(ss >> temp)
        values.push_back(temp);

    for(auto iter = values.rbegin(); iter != values.rend(); iter++)
        push(*iter);
}

void Console::intepret()
{
    if(_stack.empty())
    {
        return;
    }

    std::string curCmd = top();

    std::size_t hashCmd = std::hash<std::string>()(curCmd);
    if(hashCmd == cmd::Hash::Add)
        cmdAdd();
    else if(hashCmd == cmd::Hash::Remove)
        cmdRemove();
    else if(hashCmd == cmd::Hash::Print)
        cmdPrint();
    else if(hashCmd == cmd::Hash::Quit)
        _running = false;
    else
    {
        cerr << "Unknown command.\n";
        printHelp();
    }
}

std::string Console::top()
{
    std::string value = _stack.top();
    _stack.pop();
    return value;
}

void Console::push(std::string value)
{
    _stack.push(value);
}

void Console::clear()
{
    _stack = stack<string>();
}

void Console::cmdAdd()
{
    auto countParam = _stack.size();
    if(countParam < 2 || countParam > 2)
    {
        cerr << "Invalid number of command parameters\n";
        cerr << "\tUse: Add <fruit> <count>\n";
        return;
    }

    string param1 = top();
    string param2 = top();

    try
    {
        is_letters(param1);
        is_digits(param2);
    }
    catch (std::string &ex)
    {
        cerr << "Invalid parameter value:\n\t" << ex << endl;
        return;
    }

    stringstream ss(param2);
    int param2_dig; ss >> param2_dig;

    _bag.Add(param1, param2_dig);
}

void Console::cmdRemove()
{
    auto countParam = _stack.size();
    if(countParam < 2 || countParam > 2)
    {
        cerr << "Invalid number of command parameters\n";
        cerr << "\tUse: Remove <fruit> <count>\n";
        return;
    }

    string param1 = top();
    string param2 = top();

    try
    {
        is_letters(param1);
        is_digits(param2);
    }
    catch (std::string &ex)
    {
        cerr << "Invalid parameter value:\n\t" << ex << endl;
        return;
    }

    stringstream ss(param2);
    int param2_dig; ss >> param2_dig;

    _bag.Remove(param1, param2_dig);
}

void Console::cmdPrint()
{
    auto countParam = _stack.size();
    if(countParam != 0)
    {
        cerr << "Invalid number of command parameters\n";
        cerr << "\tUse: Print\n";
        return;
    }

    _bag.Print();
}

void Console::printHelp()
{
    cerr << "Use:\n";
    cerr << "\tAdd <fruit> <count>\t - Add the <count> of fruit <fruit> to the bag;\n";
    cerr << "\tRemove <fruit> <count>\t - Remove the <count> of fruit <fruit> from the bag;\n";
    cerr << "\tPrint\t\t\t - Display the contents of the backpack;\n";
    cerr << "\tQuit\t\t\t - Exit from the program.\n";
}

