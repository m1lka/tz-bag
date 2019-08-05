#include <iostream>
#include <string>
#include <memory>
#include "Console.h"

using namespace std;

int main()
{
    shared_ptr<Console> console;
    try {
        console.reset(new Console());
    } catch (string& ex) {
        cerr << ex << endl;
        cerr << "Exit!\n";
        return -1;
    }

    console->Run();
	
    return 0;
}
