#include <iostream>
#include <string>
#include <memory>
#include "Console.h"
#include <map>

using namespace std;

int main()
{
    shared_ptr<Console> console;
    try {
        console.reset(new Console());
    } catch (std::runtime_error& ex) {
        cerr << ex.what() << endl;
        cerr << "Exit!\n";
        return -1;
    }

    console->Run();
	
    return 0;
}
