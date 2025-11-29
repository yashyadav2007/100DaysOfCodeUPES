// gen.c
#include <stdio.h>
#include <time.h>

int main() {
    FILE *fp = fopen("log.txt", "a");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    time_t now = time(NULL);
    fprintf(fp, "Entry at: %s", ctime(&now));
    fclose(fp);

    return 0;
}





