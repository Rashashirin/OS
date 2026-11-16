
#include <stdio.h>

struct Process {
    int pid, arrival, burst;
    int completion, turnaround, waiting;
};

int main() {
    int n, time = 0;
    float totalWT = 0, totalTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);

        printf("Burst Time: ");
        scanf("%d", &p[i].burst);
    }

    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival > p[j].arrival) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // FCFS Scheduling
    for (int i = 0; i < n; i++) {

        if (time < p[i].arrival)
            time = p[i].arrival;

        time += p[i].burst;

        p[i].completion = time;

        p[i].turnaround =
            p[i].completion - p[i].arrival;

        p[i].waiting =
            p[i].turnaround - p[i].burst;

        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
            p[i].pid,
            p[i].arrival,
            p[i].burst,
            p[i].completion,
            p[i].turnaround,
            p[i].waiting);
    }

    printf("\nAverage Waiting Time = %.2f",
           totalWT / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           totalTAT / n);

    return 0;
}
