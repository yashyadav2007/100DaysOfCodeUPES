// git_commits.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

time_t random_time_between(time_t start, time_t end) {
    double diff = difftime(end, start);
    if (diff <= 0) return start;
    double r = (double)rand() / ((double)RAND_MAX + 1.0);
    time_t offset = (time_t)(r * diff);
    return start + offset;
}

int main(int argc, char **argv) {
    srand((unsigned int)(time(NULL) ^ getpid()));

    struct tm start_tm = {0};
    start_tm.tm_year = 2025 - 1900; // year 2025
    start_tm.tm_mon = 10;           // November (0-based -> 10)
    start_tm.tm_mday = 24;          // 24th
    start_tm.tm_hour = 0;
    start_tm.tm_min = 0;
    start_tm.tm_sec = 0;

    time_t start_time = mktime(&start_tm);
    time_t end_time = time(NULL);

    int commits = 0;
    if (argc > 1) {
        commits = atoi(argv[1]);
        if (commits <= 0) commits = 1;
    } else {
        printf("Enter how many commits you want to generate: ");
        if (scanf("%d", &commits) != 1 || commits <= 0) commits = 1;
    }

    for (int i = 0; i < commits; i++) {
        time_t random_time = random_time_between(start_time, end_time);
        struct tm date_tm;
        localtime_r(&random_time, &date_tm);

        char gitdate[40];
        strftime(gitdate, sizeof(gitdate), "%Y-%m-%dT%H:%M:%S", &date_tm);

        // Append a small line to dummy.txt
        FILE *fp = fopen("dummy.txt", "a");
        if (!fp) {
            perror("fopen");
            return 1;
        }
        fprintf(fp, "Commit %d on %s\n", i + 1, gitdate);
        fclose(fp);

        // Make git commit with specified author/committer dates
        char command[600];
        snprintf(command, sizeof(command),
            "GIT_AUTHOR_DATE=\"%s\" GIT_COMMITTER_DATE=\"%s\" "
            "git add dummy.txt && git commit -m \"Random commit %d (%s)\" > /dev/null 2>&1",
            gitdate, gitdate, i + 1, gitdate);

        int rc = system(command);
        if (rc != 0) {
            fprintf(stderr, "Warning: git commit %d returned code %d\n", i + 1, rc);
        } else {
            printf("Created commit %d on %s\n", i + 1, gitdate);
        }
    }

    printf("Done. Tip: run 'git log --oneline --date=iso' to inspect commits.\n");
    return 0;
}
