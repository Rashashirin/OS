
#include <stdio.h>

struct Process {
    int pid, arrival, burst;
    int completion, turnaround, waiting;
    int completed;
};

int main() {
    int n, time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].completed = 0;

        printf("\nProcess %d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);

        printf("Burst Time: ");
        scanf("%d", &p[i].burst);
    }

    // Non-preemptive SJF Scheduling
    while (completed < n) {
        int shortest = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time &&
                p[i].completed == 0) {

                if (shortest == -1 ||
                    p[i].burst < p[shortest].burst) {
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        time += p[shortest].burst;

        p[shortest].completion = time;

        p[shortest].turnaround =
            p[shortest].completion - p[shortest].arrival;

        p[shortest].waiting =
            p[shortest].turnaround - p[shortest].burst;

        p[shortest].completed = 1;
        completed++;
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

        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }

    printf("\nAverage Waiting Time = %.2f",
           totalWT / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           totalTAT / n);

    return 0;
}
