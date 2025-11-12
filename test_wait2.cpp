#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main() {
    pid_t pid;    // process id
    cout << "fork program starting\n";
    pid = fork();

    if (pid < 0)
    {
        cout << "Fork failure!\n";
        return 1;
    } 
    else if (pid == 0) 
    { 
        // Child process
        cout << "This is the child (PID: " << getpid() 
             << ", Parent PID: " << getppid() << ")\n";

        // Child creates a grandchild
        pid_t gpid = fork();

        if (gpid < 0) {
            cout << "Fork failure in child!\n";
            exit(1);
        } 
        else if (gpid == 0) 
        {
            // Grandchild process
            cout << "This is the grandchild\n";
            cout << "Grandchild PID: " << getpid() << endl;
            cout << "Parent PID (child): " << getppid() << endl;

            
            sleep(1); 
            cout << "Grandparent PID: " << getppid();
            exit(2);
        } 
        else 
        {
            // Child waits for grandchild
            int stat_val;
            pid_t gc_pid = wait(&stat_val);
            cout << "Grandchild finished: PID = " << gc_pid << endl;
            if (WIFEXITED(stat_val))
                cout << "Grandchild exited with code " << WEXITSTATUS(stat_val) << endl;
            else
                cout << "Grandchild terminated abnormally!" << endl;
            exit(9);
        }
    } 
    else 
    {
        // Parent process
        cout << "This is the parent (PID: " << getpid() << ")\n";
        int stat_val;
        pid_t child_pid = wait(&stat_val);
        cout << "Child finished: PID = " << child_pid << endl;
        if (WIFEXITED(stat_val))
            cout << "Child exited with code " << WEXITSTATUS(stat_val) << endl;
        else
            cout << "Child terminated abnormally!" << endl;
    }

    return 0;
}
