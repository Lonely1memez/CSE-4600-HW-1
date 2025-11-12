// test_exec.cpp modified (1)
#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
    cout << "Running ls with execlp\n";
    execlp("ls", "ls", "-l", nullptr);

    cout << "The program is exiting!\n";

    return 0;
}