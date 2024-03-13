#include <stdio.h>
#include <stdbool.h>

#define NUM_RESOURCES 3
#define NUM_PROCESSES 5

int available[NUM_RESOURCES] = {10, 5, 7};  // Recursos disponibles
int max_claim[NUM_PROCESSES][NUM_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

int allocation[NUM_PROCESSES][NUM_RESOURCES];
int need[NUM_PROCESSES][NUM_RESOURCES];
bool finish[NUM_PROCESSES];

bool is_safe(int process_id) {
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        if (need[process_id][i] > available[i]) {
            return false;
        }
    }
    return true;
}

void release_resources(int process_id) {
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        available[i] += allocation[process_id][i];
        allocation[process_id][i] = 0;
    }
}

int main() {
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        for (int j = 0; j < NUM_RESOURCES; ++j) {
            allocation[i][j] = 0;
            need[i][j] = max_claim[i][j];
        }
    }

    while (true) {
        bool all_finished = true;
        for (int i = 0; i < NUM_PROCESSES; ++i) {
            if (!finish[i]) {
                all_finished = false;
                break;
            }
        }
        if (all_finished) {
            printf("All processes finished successfully.\n");
            break;
        }

        int process_id = -1;
        for (int i = 0; i < NUM_PROCESSES; ++i) {
            if (!finish[i] && is_safe(i)) {
                process_id = i;
                break;
            }
        }

        if (process_id == -1) {
            printf("Unsafe state detected.\n");
            break;
        }

        printf("Executing process %d\n", process_id);
        for (int i = 0; i < NUM_RESOURCES; ++i) {
            available[i] -= need[process_id][i];
            allocation[process_id][i] += need[process_id][i];
            need[process_id][i] = 0;
        }
        finish[process_id] = true;
    }

    return 0;
}
