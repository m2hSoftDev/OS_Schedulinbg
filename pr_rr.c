#include <stdio.h>

struct Process { 
    int id, at, bt, pr, rt, ct, tat, wt, fin; 
};

int main() {
    int n, tq, time = 0, completed = 0;
    float tot_wt = 0, tot_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        p[i].fin = 0;
        printf("P%d Arrival, Burst & Priority: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].rt = p[i].bt;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    printf("\nGantt Chart:\n%d", time);

    while (completed < n) {
        int idx = -1;
        int highest_pr = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].fin && p[i].at <= time) {
                if (p[i].pr < highest_pr) {
                    highest_pr = p[i].pr;
                    idx = i;
                } else if (p[i].pr == highest_pr && p[i].at < p[idx].at) {
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        int exec = (p[idx].rt < tq) ? p[idx].rt : tq;
        
        printf(" -- P%d -- ", p[idx].id);
        time += exec;
        p[idx].rt -= exec;
        printf("%d", time);

        if (p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].fin = 1;
            completed++;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            tot_wt += p[idx].wt;
            tot_tat += p[idx].tat;
        }
    }

    printf("\n\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].pr, p[i].ct, p[i].tat, p[i].wt);

    printf("\nAvg Waiting Time: %.2f", tot_wt / n);
    printf("\nAvg Turnaround Time: %.2f\n", tot_tat / n);

    return 0;
}