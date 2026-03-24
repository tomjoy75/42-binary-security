#include <stdio.h>
#include <unistd.h>

int main() {
    printf("RUID = %d\n", getuid());
    printf("EUID = %d\n", geteuid());
    return 0;
}

