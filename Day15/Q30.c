//Q30: Write a program to reverse a given number.

/*
Sample Test Cases:
Input 1:
1234
Output 1:
4321

Input 2:
100
Output 2:
1

*/
#include <stdio.h>

int main() {
    int n;
    int reversed = 0;
    int remainder;
    printf("Enter a number: ");
    scanf("%d", &n);

    while (n > 0) {
        remainder = n % 10;
        reversed = reversed * 10 + remainder;
        n = n / 10;
    }

    printf("%d\n", reversed);

    return 0;
}
