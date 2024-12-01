#include <stdio.h>

struct Task {
    int id;
    int burst_time;
    int wait_time;
    int turnaround_time;
    int priority_level;
    int arrival_time;
};

void sortByBurstTime(struct Task tasks[], int count) {
    for (int i = 0; i < count-1; i++) {
        for (int j = 0; j < count-i-1; j++) {
            if (tasks[j].burst_time > tasks[j+1].burst_time) {
                struct Task temp = tasks[j];
                tasks[j] = tasks[j+1];
                tasks[j+1] = temp;
            }
        }
    }
}

void sortByPriority(struct Task tasks[], int count) {
    for (int i = 0; i < count-1; i++) {
        for (int j = 0; j < count-i-1; j++) {
            if (tasks[j].priority_level > tasks[j+1].priority_level) {
                struct Task temp = tasks[j];
                tasks[j] = tasks[j+1];
                tasks[j+1] = temp;
            }
        }
    }
}

void calculateWaitTime(struct Task tasks[], int count) {
    tasks[0].wait_time = 0;
    for (int i = 1; i < count; i++) {
        tasks[i].wait_time = tasks[i-1].wait_time + tasks[i-1].burst_time;
    }
}

void calculateTurnaroundTime(struct Task tasks[], int count) {
    for (int i = 0; i < count; i++) {
        tasks[i].turnaround_time = tasks[i].burst_time + tasks[i].wait_time;
    }
}

void firstComeFirstServe(struct Task tasks[], int count) {
    calculateWaitTime(tasks, count);
    calculateTurnaroundTime(tasks, count);
}

void shortestJobFirst(struct Task tasks[], int count) {
    sortByBurstTime(tasks, count);
    calculateWaitTime(tasks, count);
    calculateTurnaroundTime(tasks, count);
}

void priorityScheduling(struct Task tasks[], int count) {
    sortByPriority(tasks, count);
    calculateWaitTime(tasks, count);
    calculateTurnaroundTime(tasks, count);
}

void roundRobin(struct Task tasks[], int count, int time_quantum) {
    int remaining_burst_time[count];
    for (int i = 0; i < count; i++) {
        remaining_burst_time[i] = tasks[i].burst_time;
    }
    
    int current_time = 0;
    while (1) {
        int all_done = 1;
        for (int i = 0; i < count; i++) {
            if (remaining_burst_time[i] > 0) {
                all_done = 0;
                if (remaining_burst_time[i] > time_quantum) {
                    current_time += time_quantum;
                    remaining_burst_time[i] -= time_quantum;
                } else {
                    current_time += remaining_burst_time[i];
                    tasks[i].wait_time = current_time - tasks[i].burst_time;
                    remaining_burst_time[i] = 0;
                }
            }
        }
        if (all_done == 1)
            break;
    }
    calculateTurnaroundTime(tasks, count);
}

void shortestRemainingTimeFirst(struct Task tasks[], int count) {
    int remaining_burst_time[count];
    for (int i = 0; i < count; i++) {
        remaining_burst_time[i] = tasks[i].burst_time;
    }
    
    int completed_tasks = 0, current_time = 0, minimum_time = 1e9;
    int shortest_task = 0, finish_time;
    int task_found = 0;
    
    while (completed_tasks != count) {
        for (int j = 0; j < count; j++) {
            if ((tasks[j].arrival_time <= current_time) && (remaining_burst_time[j] < minimum_time) && remaining_burst_time[j] > 0) {
                minimum_time = remaining_burst_time[j];
                shortest_task = j;
                task_found = 1;
            }
        }
        if (task_found == 0) {
            current_time++;
            continue;
        }
        remaining_burst_time[shortest_task]--;
        minimum_time = remaining_burst_time[shortest_task];
        if (minimum_time == 0) minimum_time = 1e9;
        
        if (remaining_burst_time[shortest_task] == 0) {
            completed_tasks++;
            finish_time = current_time + 1;
            tasks[shortest_task].wait_time = finish_time - tasks[shortest_task].burst_time - tasks[shortest_task].arrival_time;
            if (tasks[shortest_task].wait_time < 0) tasks[shortest_task].wait_time = 0;
        }
        current_time++;
    }
    calculateTurnaroundTime(tasks, count);
}

void displayResults(struct Task tasks[], int count) {
    printf("\nTasks\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", tasks[i].id, tasks[i].burst_time, tasks[i].wait_time, tasks[i].turnaround_time);
    }
}

int main() {
    int count, time_quantum, choice;
    printf("Enter the number of tasks: ");
    scanf("%d", &count);
    
    struct Task tasks[count];
    for (int i = 0; i < count; i++) {
        tasks[i].id = i+1;
        printf("Enter burst time for task %d: ", i+1);
        scanf("%d", &tasks[i].burst_time);
    }
    
    printf("Choose Scheduling Algorithm:\n");
    printf("1. FCFS\n2. SJF\n3. Priority Scheduling\n4. Round Robin\n5. SRTF\n");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            firstComeFirstServe(tasks, count);
            break;
        case 2:
            shortestJobFirst(tasks, count);
            break;
        case 3:
            for (int i = 0; i < count; i++) {
                printf("Enter priority level for task %d: ", i+1);
                scanf("%d", &tasks[i].priority_level);
            }
            priorityScheduling(tasks, count);
            break;
        case 4:
            printf("Enter time quantum: ");
            scanf("%d", &time_quantum);
            roundRobin(tasks, count, time_quantum);
            break;
        case 5:
            for (int i = 0; i < count; i++) {
                printf("Enter arrival time for task %d: ", i+1);
                scanf("%d", &tasks[i].arrival_time);
            }
            shortestRemainingTimeFirst(tasks, count);
            break;
        default:
            printf("Invalid choice!\n");
            return 0;
    }
    displayResults(tasks, count);
    return 0;
}
