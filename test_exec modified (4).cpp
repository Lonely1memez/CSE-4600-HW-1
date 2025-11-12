// test_exec.cpp modified (4)
#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
    cout << "Running rm with execlp\n";
    execlp("rm", "rm", "test.txt", nullptr);

    cout << "The program is exiting!\n";

    return 0;
}
