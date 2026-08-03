#include <stdio.h>

struct Process { int id, at, bt, rt, ct, tat, wt; };

int main() {
    int n, tq, time = 0, completed = 0;
    float tot_wt = 0, tot_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("P%d Arrival & Burst time: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    printf("\nGantt Chart:\n%d", time);
    while (completed < n) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0 && p[i].at <= time) {
                done = 0;
                int exec = (p[i].rt < tq) ? p[i].rt : tq;
                printf(" -- P%d -- ", p[i].id);
                time += exec;
                p[i].rt -= exec;

                if (p[i].rt == 0) {
                    p[i].ct = time;
                    completed++;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    tot_wt += p[i].wt;
                    tot_tat += p[i].tat;
                }
                printf("%d", time);
            }
        }
        if (done) time++;
    }

    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);

    printf("\nAvg Waiting Time: %.2f", tot_wt / n);
    printf("\nAvg Turnaround Time: %.2f\n", tot_tat / n);

    return 0;
}