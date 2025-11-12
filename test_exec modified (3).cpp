// test_exec.cpp modified (3)
#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
    cout << "Running cat with execlp\n";
    execlp("cat", "cat", "test_exec.cpp", nullptr);

    cout << "The program is exiting!\n";

    return 0;
}
