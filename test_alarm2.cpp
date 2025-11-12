#include <iostream>  
#include <signal.h>
#include <unistd.h>
using namespace std;

// Handle SIGINT (Ctrl+C)
void handle_sigint(int sig) {
    cout << "\nCaught SIGINT (Ctrl+C). Press Ctrl+\\ to quit." << endl;
}

// Handle SIGQUIT (Ctrl+\)
void handle_sigquit(int sig) {
    cout << "\nCaught SIGQUIT (Ctrl+\\). Exiting now." << endl;
    _exit(0); // exit immediately
}

int main() {
    struct sigaction sa_int, sa_quit;

    // Clear the sigaction structures
    sigemptyset(&sa_int.sa_mask);
    sigemptyset(&sa_quit.sa_mask);

    sa_int.sa_handler = handle_sigint;
    sa_quit.sa_handler = handle_sigquit;

    // Set options
    sa_int.sa_flags = 0;
    sa_quit.sa_flags = 0;

    // Register signal handlers
    sigaction(SIGINT, &sa_int, NULL);
    sigaction(SIGQUIT, &sa_quit, NULL);

    cout << "Program running. Press Ctrl+C or Ctrl+\\ ..." << endl;

    // Infinite loop to keep program alive
    while (1) {
        pause(); // wait for signals
    }

    return 0;
}
