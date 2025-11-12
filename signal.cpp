// test_signal.cpp
#include <signal.h>
#include <unistd.h>
#include <iostream>

using namespace std;

// This function will be called when the program receives SIGINT (Ctrl+C)
void func(int sig)
{
    cout << "Received a signal from your program " << sig << endl;
}

int main()
{
    // Catch terminal interrupt (Ctrl+C) and handle it using func()
    (void) signal(SIGINT, func);

    // Print a message every second
    for (int i = 0; i < 20; ++i)
    {
        cout << "CSUSB CSE 4600 Operating Systems Fall 2024" << endl;
        sleep(1);
    }

    return 0;
}
