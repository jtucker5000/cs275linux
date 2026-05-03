#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Real UID: %d\n", getuid());
    printf("Effective UID: %d\n", geteuid());
    printf("Real Group ID: %d\n", getgid());
    printf("Effective Group ID: %d\n", getegid());
    return 0;
}

