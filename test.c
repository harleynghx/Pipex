
#include "pipexHeader.h"

int main(int argc, char **argv, char **envp) {
    // Print all environment variables
    for (int i = 0; envp[i] != NULL; i++) {
        printf("%s\n", envp[i]);
    }
    return 0;
}
