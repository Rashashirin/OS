
#include <stdio.h>

#define MAX 100

struct Process {
    int pid, arrival, burst, remaining;
    int completion, turnaround, waiting;
};

int main() {
    int n, quantum, time = 0, completed = 0;
    int queue[MAX], head = 0, tail = 0, count = 0;
    int added[MAX] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[MAX];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);

        printf("Burst Time: ");
        scanf("%d", &p[i].burst);

        p[i].remaining = p[i].burst;
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &quantum);

    if (n <= 0 || n > MAX || quantum <= 0) {
        printf("Invalid input!\n");
        return 1;
    }

    while (completed < n) {

        // Add newly arrived processes
        for (int i = 0; i < n; i++) {
            if (!added[i] && p[i].arrival <= time) {
                queue[tail] = i;
                tail = (tail + 1) % MAX;
                count++;
                added[i] = 1;
            }
        }

        // CPU idle
        if (count == 0) {
            time++;
            continue;
        }

        // Select process from queue
        int current = queue[head];
        head = (head + 1) % MAX;
        count--;

        // Execute for time quantum
        int execute = (p[current].remaining < quantum)
                      ? p[current].remaining : quantum;

        p[current].remaining -= execute;
        time += execute;

        // Add newly arrived processes
        for (int i = 0; i < n; i++) {
            if (!added[i] && p[i].arrival <= time) {
                queue[tail] = i;
                tail = (tail + 1) % MAX;
                count++;
                added[i] = 1;
            }
        }

        // Process completed
        if (p[current].remaining == 0) {
            completed++;
            p[current].completion = time;

            p[current].turnaround =
                p[current].completion - p[current].arrival;

            p[current].waiting =
                p[current].turnaround - p[current].burst;
        } else {
            // Add unfinished process to queue
            queue[tail] = current;
            tail = (tail + 1) % MAX;
            count++;
        }
    }

    float totalWT = 0, totalTAT = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival,
               p[i].burst,
               p[i].completion,
               p[i].turnaround,
               p[i].waiting);

        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }

    printf("\nAverage Waiting Time = %.2f",
           totalWT / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           totalTAT / n);

    return 0;
}
