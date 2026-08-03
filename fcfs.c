#include <stdio.h>

struct Process { int id, at, bt, ct, tat, wt; };

int main() {
    int n, time = 0;
    float tot_wt = 0, tot_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("P%d Arrival & Burst time: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[j].at < p[i].at) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }

    printf("\nGantt Chart:\n%d", time);
    for (int i = 0; i < n; i++) {
        if (time < p[i].at) {
            time = p[i].at;
            printf(" -- idle -- %d", time);
        }
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        tot_wt += p[i].wt;
        tot_tat += p[i].tat;
        printf(" -- P%d -- %d", p[i].id, time);
    }

    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);

    printf("\nAvg Waiting Time: %.2f", tot_wt / n);
    printf("\nAvg Turnaround Time: %.2f\n", tot_tat / n);

    return 0;
}