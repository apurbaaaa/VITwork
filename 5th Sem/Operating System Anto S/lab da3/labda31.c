#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESS 10
#define MAX_RESOURCES 10

void calculateNeed(int need[MAX_PROCESS][MAX_RESOURCES], int max[MAX_PROCESS][MAX_RESOURCES], int alloc[MAX_PROCESS][MAX_RESOURCES], int np, int nr) {
    for (int i = 0; i < np; i++)
        for (int j = 0; j < nr; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

bool isSafe(int processes[], int avail[], int max[MAX_PROCESS][MAX_RESOURCES], int alloc[MAX_PROCESS][MAX_RESOURCES], int np, int nr) {
    int need[MAX_PROCESS][MAX_RESOURCES];
    calculateNeed(need, max, alloc, np, nr);

    bool finish[MAX_PROCESS] = { false };
    int safeSeq[MAX_PROCESS], work[MAX_RESOURCES];
    
    for (int i = 0; i < nr; i++) work[i] = avail[i];

    int count = 0;
    while (count < np) {
        bool found = false;
        for (int p = 0; p < np; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < nr; j++) {
                    if (need[p][j] > work[j]) break;
                }
                if (j == nr) {
                    for (int k = 0; k < nr; k++)
                        work[k] += alloc[p][k];
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < np; i++) {
        printf("%d ", safeSeq[i]);
    }
    printf("\n");
    return true;
}

void requestResources(int processes[], int avail[], int max[MAX_PROCESS][MAX_RESOURCES], int alloc[MAX_PROCESS][MAX_RESOURCES], int np, int nr) {
    int process_num, request[MAX_RESOURCES];
    printf("Enter the process number making the request (0-%d): ", np - 1);
    scanf("%d", &process_num);

    printf("Enter the requested resources: ");
    for (int i = 0; i < nr; i++) {
        scanf("%d", &request[i]);
    }

    for (int i = 0; i < nr; i++) {
        if (request[i] > avail[i]) {
            printf("Requested resources exceed available resources. Request cannot be granted.\n");
            return;
        }
    }

    for (int i = 0; i < nr; i++) {
        if (request[i] > max[process_num][i] - alloc[process_num][i]) {
            printf("Requested resources exceed maximum claim for process. Request cannot be grant-ed.\n");
            return;
        }
    }

    for (int i = 0; i < nr; i++) {
        avail[i] -= request[i];
        alloc[process_num][i] += request[i];
        max[process_num][i] -= request[i];
    }

    if (isSafe(processes, avail, max, alloc, np, nr)) {
        printf("Request can be granted. Resources have been allocated.\n");
    } else {
        printf("Request cannot be granted as it leads to an unsafe state. Rolling back the request.\n");
        for (int i = 0; i < nr; i++) {
            avail[i] += request[i];
            alloc[process_num][i] -= request[i];
            max[process_num][i] += request[i];
        }
    }
}

int main() {
    int np, nr;
    int processes[MAX_PROCESS], avail[MAX_RESOURCES];
    int max[MAX_PROCESS][MAX_RESOURCES], alloc[MAX_PROCESS][MAX_RESOURCES];

    printf("Enter the number of processes: ");
    scanf("%d", &np);
    printf("Enter the number of resources: ");
    scanf("%d", &nr);
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < np; i++) {
        processes[i] = i;
        for (int j = 0; j < nr; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }
    printf("Enter the maximum demand matrix:\n");
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nr; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    printf("Enter the available resources: ");
    for (int i = 0; i < nr; i++) {
        scanf("%d", &avail[i]);
    }
    if (isSafe(processes, avail, max, alloc, np, nr)) {
        printf("System is in a safe state.\n");
    } else {
        printf("System is not in a safe state.\n");
    }
    char ch;
    printf("Do you want to request resources for a process? (y/n): ");
    scanf(" %c", &ch);
    if (ch == 'y' || ch == 'Y') {
        requestResources(processes, avail, max, alloc, np, nr);
    }
    return 0;
}