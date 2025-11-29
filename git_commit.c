// gen.c
#include <stdio.h>
#include <time.h>

int main() {
    FILE *fp = fopen("data.txt", "a");
    if (!fp) {
        perror("File error");
        return 1;
    }

    time_t now = time(NULL);
    fprintf(fp, "Auto entry at %s", ctime(&now));
    fclose(fp);

    return 0;
}