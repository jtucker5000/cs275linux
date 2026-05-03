#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <math.h>

volatile sig_atomic_t running = 1;

void handle_sigint(int sig) {
    running = 0;
}

void run_idle_worker() {
    printf("Idle worker started (PID %d)\n", getpid());
    while (running) {
        sleep(2); // minimal CPU usage
    }
}

void run_cpu_worker() {
    printf("CPU worker started (PID %d)\n", getpid());

    volatile double result = 0;

    while (running) {
        for (int i = 0; i < 1000000; i++) {
            result += sqrt(i) * sin(i);
        }
    }
}

int main() {
    signal(SIGINT, handle_sigint);

    printf("Parent PID: %d\n", getpid());

    pid_t children[3];

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            signal(SIGINT, handle_sigint);

            if (i < 2) {
                run_idle_worker();
            } else {
                run_cpu_worker();
            }
            exit(0);
        } else if (pid > 0) {
            children[i] = pid;
        } else {
            perror("fork failed");
            exit(1);
        }
    }

    printf("Spawned 3 children (2 idle, 1 CPU-intensive).\n");
    printf("Press Ctrl+C to exit.\n");

    // Parent waits until Ctrl+C
    while (running) {
        sleep(1);
    }

    printf("Shutting down...\n");

    // Kill children
    for (int i = 0; i < 3; i++) {
        kill(children[i], SIGTERM);
    }

    // Reap children
    for (int i = 0; i < 3; i++) {
        waitpid(children[i], NULL, 0);
    }

    printf("Parent exiting.\n");

    return 0;
}

