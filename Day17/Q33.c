//Q33: Write a program to check if a number is an Armstrong number.

/*
Sample Test Cases:
Input 1:
153
Output 1:
Armstrong

Input 2:
123
Output 2:
Not Armstrong

*/
#include <stdio.h>

int main() {
    int num, original, rem, digits = 0, sum = 0;
    printf("Enter an integer: ");
    scanf("%d", &num);

    original = num;

    int temp = num;
    if (temp == 0) {
        digits = 1;
    } else {
        while (temp != 0) {
            temp /= 10;
            digits++;
        }
    }

    temp = num;

    while (temp != 0) {
        rem = temp % 10;

        int power = 1;
        for (int i = 0; i < digits; i++) {
            power = power * rem;
        }
        sum = sum + power;
        temp = temp / 10;
    }

    if (sum == original) {
        printf("Armstrong\n");
    } else {
        printf("Not Armstrong\n");
    }

    return 0;
}

