#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
     {
        cerr << "Usage: " << argv[0] << " <command> [arguments...]" << endl;
        return 1;
    }

    FILE *fpi;
    char buffer[BUFSIZ + 1];
    int chars_read;

    // Clear buffer
    memset(buffer, 0, sizeof(buffer));

    // Build command using strcpy and strcat
    char command[256];
    strcpy(command, argv[1]); // start with the first command word

    // Add the rest of the arguments separated by spaces
    for (int i = 2; i < argc; ++i) 
    {
        strcat(command, " ");
        strcat(command, argv[i]);
    }

    // Open the pipe to execute the command
    fpi = popen(command, "r");

    if (fpi != NULL) 
    {
        chars_read = fread(buffer, sizeof(char), BUFSIZ, fpi);
        if (chars_read > 0)
            cout << "Output from pipe: " << buffer << endl;

        pclose(fpi);
        return 0;
    }

    return 1;
}