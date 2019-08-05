#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "helper.h"
#include <stack>
#include <functional>
#include <memory>

#include "FruitBagProvider.h"
#include "Services/FileFruitService.h"

namespace cmd {

const static std::string cAdd("Add");
const static std::string cRemove("Remove");
const static std::string cPrint("Print");
const static std::string cQuit("Quit");

namespace Hash
{
    const static std::size_t Add = std::hash<std::string>()(cAdd);
    const static std::size_t Remove = std::hash<std::string>()(cRemove);
    const static std::size_t Print = std::hash<std::string>()(cPrint);
    const static std::size_t Quit = std::hash<std::string>()(cQuit);
};

}

class Console
{
public:
    Console();
	
    void Run()
    {
        while(_running)
            Update();
    }
	
private:

    void Update()
    {
        readComand();
        intepret();
        clear();
    }

    std::shared_ptr<FileFruitService> _service;
    FruitBagProvider _bag;
	
    void readComand();
    void intepret();

    std::stack<std::string> _stack;
    std::string top();
    void push(std::string value);
    void clear();

    bool _running;

    void cmdAdd();
    void cmdRemove();
    void cmdPrint();
    void printHelp();
};

#endif
