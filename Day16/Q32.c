//Q32: Write a program to check if a number is a palindrome.

/*
Sample Test Cases:
Input 1:
121
Output 1:
Palindrome

Input 2:
123
Output 2:
Not palindrome
*/
#include <stdio.h>

int main() {
    int n;
    int reversedNum = 0;
    int originalNum;
    int remainder;
    printf("Enter an integer: ");
    scanf("%d", &n);

    originalNum = n;

    while (n > 0) {
        remainder = n % 10;
        reversedNum = reversedNum * 10 + remainder;
        n = n / 10;
    }

    if (originalNum == reversedNum) {
        printf("Palindrome\n");
    } else {
        printf("Not palindrome\n");
    }

    return 0;
}
