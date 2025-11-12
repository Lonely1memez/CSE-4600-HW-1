// test_exec.cpp modified (2)
#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
    cout << "Running echo with execlp\n";
    execlp("echo", "echo", "Hello from CSUSB CSE 4600 Section 01 Fall 2024", nullptr);

    cout << "The program is exiting!\n";

    return 0;
}
