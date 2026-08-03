#include <stdio.h>

struct Process { int id, at, bt, pr, rt, ct, tat, wt; };

int main() {
    int n, time = 0, completed = 0, prev = -1;
    float tot_wt = 0, tot_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("P%d Arrival, Burst & Priority: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].rt = p[i].bt;
    }

    printf("\nGantt Chart:\n%d", time);
    while (completed < n) {
        int idx = -1, min_pr = 1e9;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                if (p[i].pr < min_pr) {
                    min_pr = p[i].pr;
                    idx = i;
                } else if (p[i].pr == min_pr && p[i].at < p[idx].at) {
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        if (prev != idx) {
            printf(" -- P%d -- ", p[idx].id);
            prev = idx;
        }

        p[idx].rt--;
        time++;

        if (p[idx].rt == 0) {
            p[idx].ct = time;
            completed++;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            tot_wt += p[idx].wt;
            tot_tat += p[idx].tat;
        }

        printf("%d", time);
    }

    printf("\n\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].pr, p[i].ct, p[i].tat, p[i].wt);

    printf("\nAvg Waiting Time: %.2f", tot_wt / n);
    printf("\nAvg Turnaround Time: %.2f\n", tot_tat / n);

    return 0;
}