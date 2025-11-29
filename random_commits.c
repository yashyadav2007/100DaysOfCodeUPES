/*
 random_commits.c
 Create randomized empty git commits dated between 2025-08-24 and "now".
 Compile: gcc random_commits.c -o random_commits
 Usage:   ./random_commits [NUM_COMMITS]
 Defaults to 10 commits if no argument provided.

 NOTE: Run this in the root of your git repository.
*/

#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int num = 10;
    if (argc >= 2) {
        num = atoi(argv[1]);
        if (num <= 0) {
            fprintf(stderr, "Usage: %s [NUM_COMMITS]\n", argv[0]);
            return 1;
        }
    }

    /* Start date: 2025-08-24 00:00:00 local */
    struct tm start_tm = {0};
    start_tm.tm_year = 2025 - 1900;
    start_tm.tm_mon  = 8 - 1;    /* August */
    start_tm.tm_mday = 24;
    start_tm.tm_hour = 0;
    start_tm.tm_min  = 0;
    start_tm.tm_sec  = 0;
    start_tm.tm_isdst = -1; /* let mktime determine DST */

    time_t start_time = mktime(&start_tm);
    if (start_time == (time_t)-1) {
        fprintf(stderr, "Failed to compute start time\n");
        return 1;
    }

    /* End time: now */
    time_t end_time = time(NULL);
    if (end_time == (time_t)-1) {
        fprintf(stderr, "Failed to get current time\n");
        return 1;
    }

    if (start_time > end_time) {
        fprintf(stderr, "Start date is after now. Aborting.\n");
        return 1;
    }

    /* confirm in git repo */
    if (system("git rev-parse --is-inside-work-tree > /dev/null 2>&1") != 0) {
        fprintf(stderr, "Not inside a git repository. cd into your repo first.\n");
        return 1;
    }

    /* Recommend user to be on a new branch (not enforced) */
    printf("Creating %d randomized commit(s) between 2025-08-24 and now.\n", num);
    printf("Recommend: run on a new branch (git checkout -b random-dates-demo) before pushing.\n\n");

    /* Seed RNG */
    srand((unsigned int)(time(NULL) ^ getpid()));

    for (int i = 1; i <= num; ++i) {
        double r = rand() / (RAND_MAX + 1.0); /* [0,1) */
        time_t rand_t = start_time + (time_t)((end_time - start_time + 1) * r);

        /* Convert to local time struct and format RFC-like with numeric timezone */
        struct tm lt;
        localtime_r(&rand_t, &lt);

        char datestr[64];
        /* Format: 2025-10-02T18:34:12+0530  -> %Y-%m-%dT%H:%M:%S%z */
        if (strftime(datestr, sizeof(datestr), "%Y-%m-%dT%H:%M:%S%z", &lt) == 0) {
            fprintf(stderr, "strftime failed\n");
            return 1;
        }

        /* Escape double quotes in message not needed here, we avoid them */
        char msg[200];
        snprintf(msg, sizeof(msg), "randomized commit #%d — author date %s", i, datestr);

        /* Build command. Prefix environment variables so git sees dates for this commit.
           Use single quotes around %s to avoid shell mangling if timezone contains + sign.
           On POSIX shells this is fine. */
        char cmd[512];
        snprintf(cmd, sizeof(cmd),
                 "GIT_AUTHOR_DATE='%s' GIT_COMMITTER_DATE='%s' git commit --allow-empty -m \"%s\"",
                 datestr, datestr, msg);

        int rc = system(cmd);
        if (rc != 0) {
            fprintf(stderr, "Command failed (rc=%d):\n%s\n", rc, cmd);
            return 1;
        }

        printf("[%d/%d] Created commit dated: %s\n", i, num, datestr);
    }

    printf("\nDone. Verify with:\n");
    printf("  git log --pretty=format:\"%%h  %%ad  %%s\" --date=iso | head -n %d\n", num + 5);
    return 0;
}
